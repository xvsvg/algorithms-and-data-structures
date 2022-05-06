#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("knapsack.in");
    ofstream out("knapsack.out");
    in.tie(0)->sync_with_stdio(false);

    int s, n;
    in >> s >> n;

    vector<int> v(n);
    // dp[i] -- could be get the number of elements of total weight i;
    vector<int> dp(10010, 0);
    dp[0] = 1;

    for (int i = 0; i < n; ++i)
    {
        in >> v[i];

        for (int j = s; j >= v[i]; --j)
        {
            if (dp[j - v[i]] == 1)
                dp[j] = 1;
        }
    }

    int j;
    for (j = s;; j--)
    {
        if (dp[j] > 0)
            break;
    }

    out << j;

    return 0;
}