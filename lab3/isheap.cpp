#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    freopen("isheap.in", "r", stdin);
    freopen("isheap.out", "w", stdout);
 
    cin.tie(0)->sync_with_stdio(false);
 
    int n;
 
    cin >> n;
 
    vector<long long> array(n);
 
    for (auto &e : array)
        cin >> e;
 
    for (long long i = 0; i < n; i++)
    {
        if (2 * i + 1 <= n - 1)
            if (array[i] > array[2 * i + 1])
            {
                cout << "NO" << endl;
                return 0;
            }
 
        if (2 * i + 2 <= n - 1)
            if (array[i] > array[2 * i + 2])
            {
                cout << "NO" << endl;
                return 0;
            }
    }
    cout << "YES" << endl;
    return 0;
}