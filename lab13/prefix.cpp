#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("prefix.in");
    ofstream out("prefix.out");
    in.tie(0)->sync_with_stdio(false);

    string s;
    in >> s;

    vector<int> ans(s.size() + 1, -1);

    int k;
    for (int i = 1; i <= s.size(); ++i)
    {
        k = ans[i - 1];

        while (k != -1 && s[k] != s[i - 1])
            k = ans[k];

        ans[i] = k + 1;
    }

    for (int i = 1; i <= s.size(); ++i)
    {
        out << ans[i] << ' ';
    }

    return 0;
}