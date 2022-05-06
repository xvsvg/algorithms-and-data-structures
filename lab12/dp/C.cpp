#include <bits/stdc++.h>

using namespace std;

string ans;

void naiveLCS(string &a, string &b)
{
	if (b.size() == 0)
	{
		return;
	}

	if (a.size() == 1 && b.find(a[0]) != string::npos)
	{
		ans.push_back(a[0]);
		return;
	}
}

vector<short> getLCS(string &a, string &b)
{
	vector<short> prev(b.size() + 1, 0);
	vector<short> cur(b.size() + 1, 0);

	for (short i = 0; i < a.size(); ++i)
	{
		prev = cur;

		for (short j = 0; j < b.size(); ++j)
		{
			if (a[i] == b[j])
			{
				cur[j + 1] = prev[j] + 1;
			}
			else
			{
				cur[j + 1] = max(cur[j], prev[j + 1]);
			}
		}
	}

	return cur;
}

void solve(string &a, string &b)
{
	if (a.size() <= 1 || b.size() < 1)
		return naiveLCS(a, b);

	short adelimiter = a.size() / 2;

	string prefa = a.substr(0, adelimiter);
	string sufa = a.substr(adelimiter);
	string revb = b;

	vector<short> left = getLCS(prefa, b);

	reverse(sufa.begin(), sufa.end());
	reverse(revb.begin(), revb.end());

	vector<short> right = getLCS(sufa, revb);

	short max = 0;
	short bdelimiter = 0;

	reverse(right.begin(), right.end());

	for (short j = 0; j <= b.size(); ++j)
	{
		if (left[j] + right[j] > max)
		{
			max = left[j] + right[j];
			bdelimiter = j;
		}
	}

	sufa = a.substr(adelimiter);
	string prefb = b.substr(0, bdelimiter);
	string sufb = b.substr(bdelimiter);

	solve(prefa, prefb);
	solve(sufa, sufb);
}

int main()
{
	cin.tie(0)->sync_with_stdio(false);

	string a, b;
	cin >> a >> b;

	(a.size() > b.size()) ? solve(a, b) : solve(b, a);

	cout << ans;

	cout << '\n';

	return 0;
}