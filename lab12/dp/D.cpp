#include <bits/stdc++.h>
#include <fstream>

using namespace std;

long long solve(int i, int j, vector<vector<long long>> &dp, int n, int m)
{
    if (i >= 0 && i < n && j >= 0 && j < m)
    {
        if (dp[i][j] == -1)
            dp[i][j] = solve(i - 2, j - 1, dp, n, m) + solve(i - 2, j + 1, dp, n, m) + solve(i - 1, j - 2, dp, n, m) + solve(i + 1, j - 2, dp, n, m);
    }
    else
        return 0;
    return dp[i][j];
}

int main()
{
    ifstream in("knight2.in");
    ofstream out("knight2.out");
    in.tie(0)->sync_with_stdio(false);

    short n, m;
    in >> n >> m;

    vector<vector<long long>> dp(n, vector<long long>(m, -1));
    dp[0][0] = 1;

    out << solve(n - 1, m - 1, dp, n, m);

    return 0;
}