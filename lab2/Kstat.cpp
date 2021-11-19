#include <bits/stdc++.h>
 
using namespace std;
 
int FindKStat(vector<int32_t> &array, int left, int right, int k)
{
    int i = left;
 
    int j = right;
 
    int32_t mid = array[(left + right) / 2];
 
    while (i <= j)
    {
 
        while (array[i++] < mid)
            ;
 
        while (array[j--] > mid)
            ;
 
        i--;
        j++;
 
        if (i <= j)
            swap(array[i++], array[j--]);
    }
 
    if (j > left && k <= j)
        FindKStat(array, left, j, k);
 
    if (i < right && k >= i)
        FindKStat(array, i, right, k);
 
    return array[k];
}
 
int main()
{
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
 
    int n, k;
    cin >> n >> k;
 
    vector<int> ElementsOfFormula(3);
 
    for (int i = 0; i < 3; i++)
        cin >> ElementsOfFormula[i];
 
    vector<int32_t> array(n);
 
    for (int i = 0; i < 2; i++)
        cin >> array[i];
 
    for (int i = 2; i < n; i++)
    {
        array[i] = ElementsOfFormula[0] * array[i - 2] + ElementsOfFormula[1] * array[i - 1] + ElementsOfFormula[2];
    }
 
    cout << FindKStat(array, 0, n - 1, k - 1);
    return 0;
}