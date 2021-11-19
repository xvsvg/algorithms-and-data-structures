#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("smallsort.in");
    ofstream out("smallsort.out");

    int n;
    in >> n;
    vector<pair<int, double>> array(n);

    for (int i = 0; i < n; i++)
    {
        array[i].first = i;
        in >> array[i].second;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (array[j].second > array[j + 1].second)
            {
                swap(array[j].second, array[j + 1].second);
                swap(array[j].first, array[j + 1].first);
            }
        }
    }
    out << array[0].first + 1 << ' ' << array[n / 2].first + 1 << ' ' << array[n - 1].first + 1 << endl;
    return 0;
}