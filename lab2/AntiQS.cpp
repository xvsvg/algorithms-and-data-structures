#include <bits/stdc++.h>
 
using namespace std;
 
void AntiQSort(vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
        swap(array[i], array[i / 2]);
}
 
int main()
{
    freopen("antiqs.in", "r", stdin);
    freopen("antiqs.out", "w", stdout);
 
    int n;
 
    cin >> n;
 
    vector<int> vec;
 
    for (int i = 0; i < n; i++)
        vec.push_back(i+1);
 
    AntiQSort(vec);
 
    for (int e : vec)
        cout << e << ' ';
    return 0;
}