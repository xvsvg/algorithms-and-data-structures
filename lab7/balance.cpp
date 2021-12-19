#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct node
{
    int value;
    int left;
    int right;
    int height;
    int balance;
};

void getBalance(vector<node> &nodes, int node)
{
    if (node != -1)
    {
        getBalance(nodes, nodes[node].right);
        getBalance(nodes, nodes[node].left);
        nodes[node].height = max(nodes[nodes[node].right].height, nodes[nodes[node].left].height) + 1;
        nodes[node].balance = nodes[nodes[node].right].height - nodes[nodes[node].left].height;
    }
}

int main()
{
    ifstream in("balance.in");
    ofstream out("balance.out");
    in.tie(NULL)->sync_with_stdio(false);

    int n;
    in >> n;

    vector<node> nodes(n);

    for (int i = 0; i < n; i++)
    {
        in >> nodes[i].value >> nodes[i].left >> nodes[i].right;
        nodes[i].height = 0;
        nodes[i].left--;
        nodes[i].right--;
    }

    getBalance(nodes, 0);

    for (int i = 0; i < n; i++)
        out << nodes[i].balance << '\n';

    return 0;
}