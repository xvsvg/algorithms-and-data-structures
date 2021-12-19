#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class node
{
public:
    int key;
    int height;
    node *left;
    node *right;

    int getHeight(node *x)
    {
        return x ? x->height : 0;
    }

    node(int key, node *left = nullptr, node *right = nullptr)
    {
        this->key = key;
        this->left = left;
        this->right = right;
        this->height = max(getHeight(left), getHeight(right)) + 1;
    }
};

node *root = nullptr;

void evaluateHeight(node *x)
{
    int left = x->getHeight(x->left);
    int right = x->getHeight(x->right);
    x->height = (left > right ? left : right) + 1;
}

node *rightRotate(node *x)
{
    node *support = x->left;
    x->left = support->right;
    support->right = x;
    evaluateHeight(x);
    evaluateHeight(support);
    return support;
}

node *leftRotate(node *x)
{
    node *support = x->right;
    x->right = support->left;
    support->left = x;
    evaluateHeight(x);
    evaluateHeight(support);
    return support;
}

int getBalance(node *x)
{
    return x->getHeight(x->right) - x->getHeight(x->left);
}

node *rebalance(node *x)
{
    evaluateHeight(x);
    if (getBalance(x) == 2)
    {
        if (getBalance(x->right) < 0)
            x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    if (getBalance(x) == -2)
    {
        if (getBalance(x->left) > 0)
            x->left = leftRotate(x->left);
        return rightRotate(x);
    }
    return x;
}

node *insert(node *x, int key)
{
    if (!x)
        return new node(key);
    if (x->key > key)
        x->left = insert(x->left, key);
    else if (x->key < key)
        x->right = insert(x->right, key);
    return rebalance(x);
}

node *getMax(node *x)
{
    return x->right ? getMax(x->right) : x;
}

node *eraseMax(node *x)
{
    if (!x)
        return nullptr;
    if (x->right == nullptr)
        return x->left;
    x->right = eraseMax(x->right);
    return rebalance(x);
}

node *erase(node *x, int key)
{
    if (!x)
        return nullptr;
    if (x->key > key)
        x->left = erase(x->left, key);
    else if (x->key < key)
        x->right = erase(x->right, key);
    else
    {
        node *support = x->left;
        node *right = x->right;
        delete (x);
        if (!support)
            return right;
        node *max = getMax(support);
        max->left = eraseMax(support);
        max->right = right;
        return rebalance(max);
    }
    return rebalance(x);
}

bool exists(node *x, int key)
{
    if (!x)
        return false;
    if (x->key > key)
        exists(x->left, key);
    else if (x->key < key)
        exists(x->right, key);
    else
        return x->key == key;
}

int main()
{
    ifstream in("avlset.in");
    ofstream out("avlset.out");
    in.tie(NULL)->sync_with_stdio(false);

    char command;
    int n, number;
    in >> n;

    for (int i = 0; i < n; ++i)
    {
        in >> command >> number;
        if (command == 'A')
        {
            root = insert(root, number);
            if (root != nullptr)
                out << getBalance(root) << '\n';
            else
                out << '0' << '\n';
        }
        if (command == 'D')
        {
            root = erase(root, number);
            if (root != nullptr)
                out << getBalance(root) << '\n';
            else
                out << '0' << '\n';
        }
        if (command == 'C')
        {
            if (exists(root, number))
                out << 'Y' << '\n';
            else
                out << 'N' << '\n';
        }
    }
    return 0;
}