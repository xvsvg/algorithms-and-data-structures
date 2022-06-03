#include <bits/stdc++.h>
#include <fstream>

using namespace std;

vector<int> pref_func(const string &s)
{
    vector<int> p(s.size(), 0);

    int k;
    for (int i = 1; i < s.size(); ++i)
    {
        k = p[i - 1];

        while (k > 0 && s[k] != s[i])
            k = p[k - 1];

        if (s[i] == s[k])
            k++;

        p[i] = k;
    }

    return p;
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    string s;
    int n;
    cin >> n >> s;

    s += '#';
    vector<int> pref = pref_func(s);
    vector<vector<int>> kmp_machine(s.size(), vector<int>(n));

    for (int i = 0; i < s.size(); ++i)
    {
        for (char c = 'a'; c < 'a' + n; ++c)
        {
            if (i > 0 && c != s[i])
            {
                kmp_machine[i][c - 'a'] = kmp_machine[pref[i - 1]][c - 'a'];
            }
            else
            {
                kmp_machine[i][c - 'a'] = i + (int)(c == s[i]);
            }
        }
    }

    for (auto &i : kmp_machine)
    {
        for (auto &j : i)
        {
            cout << j << ' ';
        }
        cout << "\n";
    }
    return 0;
}