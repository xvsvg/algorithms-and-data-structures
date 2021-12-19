#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct triplet
{
    int key;
    int left;
    int right;
};

class node
{
public:
    int height;
    int key;
    node *left;
    node *right;

    int getHeight(node *x)
    {
        return x ? x->height : 0;
    }

    node(int key, int height = 0, node *left = nullptr, node *right = nullptr)
    {
        this->key = key;
        this->height = max(getHeight(left), getHeight(right)) + 1;
        this->left = left;
        this->right = right;
    }
};

void evaluateHeight(node *x)
{
    int left = x->getHeight(x->left);
    int right = x->getHeight(x->right);
    x->height = (right >= left ? right : left) + 1;
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

node *rightRotate(node *x)
{
    node *support = x->left;
    x->left = support->right;
    support->right = x;
    evaluateHeight(x);
    evaluateHeight(support);
    return support;
}

int getFactor(node *x)
{
    return x->getHeight(x->right) - x->getHeight(x->left);
}

node *rebalance(node *x)
{
    evaluateHeight(x);
    if (getFactor(x->right) < 0)
        x->right = rightRotate(x->right);
    return leftRotate(x);
}

node *root = nullptr;

void link_nodes(vector<triplet> &input)
{
    vector<node *> tt(input.size());

    for (int i = tt.size() - 1; i >= 0; i--)
    {
        tt[i] = new node(input[i].key, 1, (input[i].left != -1 ? tt[input[i].left] : nullptr), input[i].right != -1 ? tt[input[i].right] : nullptr);
    }
    root = tt[0];
}

int newReference = 1;
void bigLeftRotateForInput(vector<triplet> &input, node *root, int oldReference)
{
    input[oldReference].key = root->key;
    if (root->left == nullptr)
        input[oldReference].left = 0;
    else
    {
        ++newReference;
        input[oldReference].left = newReference;
        bigLeftRotateForInput(input, root->left, newReference - 1);
    }
    if (root->right == nullptr)
        input[oldReference].right = 0;
    else
    {
        ++newReference;
        input[oldReference].right = newReference;
        bigLeftRotateForInput(input, root->right, newReference - 1);
    }
}

int main()
{
    ifstream in("rotation.in");
    ofstream out("rotation.out");

    in.tie(NULL)->sync_with_stdio(false);

    int n;
    in >> n;

    vector<triplet> input(n);

    for (int i = 0; i < n; i++)
    {
        in >> input[i].key >> input[i].left >> input[i].right;
        input[i].right--;
        input[i].left--;
    }

    link_nodes(input);
    root = rebalance(root);
    bigLeftRotateForInput(input, root, 0);

    out << n << '\n';
    for (int i = 0; i < n; i++)
    {
        out << input[i].key << ' ' << input[i].left << ' ' << input[i].right << '\n';
    }

    return 0;
}
