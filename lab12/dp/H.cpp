#include <bits/stdc++.h>

using namespace std;

const int base = 1e9;

int solve(vector<vector<int>> &dp, vector<int> &shirts, int left, int right)
{
    for (int gap = 1; gap < right; ++gap)
    {
        for (int i = 0; i < right - gap; ++i)
        {
            int j = gap + i;

            if (shirts[i] == shirts[j])
            {
                dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] + 1) % base;
            }
            else
            {
                dp[i][j] = (dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1]) % base;

                if (dp[i][j] < 0)
                    dp[i][j] += base;
            }
        }
    }

    return dp[0][right - 1];
}

int main()
{
    short n;
    cin >> n;

    // dp[i][j]-- quantity of palindroms in range[i, j]
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<int> shirts(n);

    for (int i = 0; i < n; i++)
    {
        cin >> shirts[i];

        dp[i][i] = 1;
    }

    cout << solve(dp, shirts, 0, n);

    return 0;
}