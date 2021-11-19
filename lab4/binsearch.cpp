#include <fstream>
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream in("binsearch.in");
ofstream out("binsearch.out");
 
void bsearch(vector<int> &array, int x)
{
    int left = 0;
    int right = array.size() - 1;
 
    pair<int, int> result(-1, -1);
 
    while (right - left > 1)
    {
        int mid = (right + left) >> 1;
 
        if (array[mid] < x)
            left = mid;
 
        else
            right = mid;
    }
 
    if (array[left] == x)
        result.first = left + 1;
    else if (array[right] == x)
        result.first = right + 1;
 
    left = 0;
    right = array.size() - 1;
 
    while (right - left > 1)
    {
        int mid = (right + left) >> 1;
 
        if (array[mid] <= x)
            left = mid;
 
        else
            right = mid;
    }
 
    if (array[right] == x)
        result.second = right + 1;
    else if (array[left] == x)
        result.second = left + 1;
 
    out << result.first << ' ' << result.second << endl;
}
 
int main()
{
    int n, m;
    in >> n;
 
    vector<int> array(n);
    int number;
 
    for (auto &x : array)
        in >> x;
 
    in >> m;
 
    for (int i = 0; i < m; i++)
    {
        in >> number;
 
        bsearch(array, number);
    }
    return 0;
}