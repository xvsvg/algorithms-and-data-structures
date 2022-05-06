#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void solve(vector<vector<int>> &tree, vector<vector<int>> &dp, int root, vector<int> &weights)
{
    dp[root][0] = 0;
    dp[root][1] = weights[root];

    for (auto &i : tree[root])
    {
        solve(tree, dp, i, weights);
    }

    for (auto &i : tree[root])
    {
        dp[root][0] += max(dp[i][0], dp[i][1]);
        dp[root][1] += dp[i][0];
    }
}

int main()
{
    ifstream in("selectw.in");
    ofstream out("selectw.out");
    in.tie(0)->sync_with_stdio(false);

    int n;
    in >> n;

    vector<vector<int>> tree(n);
    vector<int> weights(n, 0);
    int v, root;

    for (int i = 0; i < n; ++i)
    {
        in >> v >> weights[i];

        if (v == 0)
        {
            root = i;
            continue;
        }

        tree[v - 1].push_back(i);
    }

    // dp[v][0] -- sum of weights of vertices excluding root of independent set with root in vertex i
    // dp[v][1] -- sum of weights of vertices including root of independent set with root in vertex i
    vector<vector<int>> dp(n, vector<int>(2, 0));

    solve(tree, dp, root, weights);

    out << max(dp[root][0], dp[root][1]);

    return 0;
}