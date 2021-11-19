#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("smallsort.in");
    ofstream out("smallsort.out");

    int n;
    in >> n;

    vector<int> array(n);

    for (int &x : array)
        in >> x;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (array[j] > array[j + 1])
                swap(array[j], array[j + 1]);

    for (int i = 0; i < n; i++)
        out << array[i] << ' ';

    return 0;
}