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
        height = max(getHeight(left), getHeight(right)) + 1;
    }
};

int input[200001][3];
node *root = nullptr;

void link_nodes(int n)
{
    vector<node *> tt(n);
    for (int oldReference = n - 1; oldReference >= 0; --oldReference)
        tt[oldReference] = new node(input[oldReference][0], (input[oldReference][1] != -1 ? tt[input[oldReference][1]] : nullptr), (input[oldReference][2] != -1 ? tt[input[oldReference][2]] : nullptr));
    root = (n ? tt[0] : nullptr);
}

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

int newReference = 1;
void insertionForInput(node *x, int oldReference)
{
    input[oldReference][0] = x->key;
    if (x->left != nullptr)
    {
        ++newReference;
        input[oldReference][1] = newReference;
        insertionForInput(x->left, newReference - 1);
    }
    else
        input[oldReference][1] = 0;
    if (x->right != nullptr)
    {
        ++newReference;
        input[oldReference][2] = newReference;
        insertionForInput(x->right, newReference - 1);
    }
    else
        input[oldReference][2] = 0;
}

node *insert(node *x, int key)
{
    if (!x)
        return new node(key);
    if (x->key > key)
        x->left = insert(x->left, key);
    else
        x->right = insert(x->right, key);
    return rebalance(x);
}

int main()
{
    ifstream in("addition.in");
    ofstream out("addition.out");

    int n, newElement;
    in >> n;
    if (n == 0)
    {
        in >> newElement;
        out << 1 << '\n';
        out << newElement << ' ' << 0 << ' ' << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i)
    {
        in >> input[i][0] >> input[i][1] >> input[i][2];
        input[i][1]--;
        input[i][2]--;
    }
    in >> newElement;

    link_nodes(n);
    root = insert(root, newElement);
    insertionForInput(root, 0);

    out << n + 1 << '\n';
    for (int i = 0; i <= n; ++i)
    {
        out << input[i][0] << ' ' << input[i][1] << ' ' << input[i][2] << '\n';
    }
    return 0;
}