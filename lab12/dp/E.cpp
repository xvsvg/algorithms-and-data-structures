#include <bits/stdc++.h>

using namespace std;

vector<short> getChildren(vector<vector<short>> &tree, short v)
{
    return tree[v];
}

vector<short> getGrandchildren(vector<vector<short>> &tree, short v)
{
    vector<short> result;
    vector<short> children = getChildren(tree, v);

    for (int i = 0; i < children.size(); ++i)
    {
        for (int j = 0; j < tree[children[i]].size(); ++j)
        {
            result.push_back(tree[children[i]][j]);
        }
    }

    return result;
}

short solve(vector<vector<short>> &tree, vector<short> &dp, short root)
{
    if (dp[root] != -1)
        return dp[root];

    short childrenSum = 0, grandchildrenSum = 0;

    vector<short> children = getChildren(tree, root);
    vector<short> grandchildren = getGrandchildren(tree, root);

    for (int i = 0; i < children.size(); ++i)
    {
        childrenSum += solve(tree, dp, children[i]);
    }

    for (int i = 0; i < grandchildren.size(); ++i)
    {
        grandchildrenSum += solve(tree, dp, grandchildren[i]);
    }

    dp[root] = max(short(1 + grandchildrenSum), childrenSum);
    return dp[root];
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    short n;
    cin >> n;

    vector<vector<short>> tree(n);
    short v, root;

    for (int i = 0; i < n; ++i)
    {
        cin >> v;

        if (v == 0)
        {
            root = i;
            continue;
        }

        tree[v - 1].push_back(i);
    }

    if (n == 1)
    {
        cout << 1 << '\n';
        return 0;
    }

    // dp[i] -- number of vertices in considering set with root i
    vector<short> dp(n, -1);

    cout << solve(tree, dp, root) << '\n';

    return 0;
}