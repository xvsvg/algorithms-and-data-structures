#include <bits/stdc++.h>

using namespace std;

int main()
{
    unsigned n;
    cin >> n;

    vector<pair<int, int>> v(n, {0, n}); // <element, index of element that should be placed before v[i] in optimal subsequence>

    for (int i = 0; i < n; ++i)
    {
        cin >> v[i].first;
    }

    vector<int> dp(n + 1, INT_MAX); // dp[i] -- number with which sequence with length i ends
    dp[0] = -(INT_MAX);

    vector<int> sequence(n + 1, -1); // index of element with which optimal subsequence of length i ends
    int insertPos;

    for (int i = 0; i < n; ++i)
    {
        insertPos = static_cast<int>(upper_bound(dp.begin(), dp.end(), v[i].first) - dp.begin());

        if (dp[insertPos - 1] < v[i].first)
        {
            dp[insertPos] = v[i].first;
            sequence[insertPos] = i;
            v[i].second = sequence[insertPos - 1];
        }
    }

    int pointer = static_cast<int>(lower_bound(dp.begin(), dp.end(), INT_MAX) - dp.begin()) - 1;

    cout << pointer << endl;

    vector<int> ans;
    ans.push_back(v[sequence[pointer]].first);
    pointer = v[sequence[pointer]].second;

    while (pointer != -1)
    {
        ans.push_back(v[pointer].first);
        pointer = v[pointer].second;
    }

    reverse(ans.begin(), ans.end());

    for (auto &i : ans)
    {
        cout << i << ' ';
    }

    return 0;
}