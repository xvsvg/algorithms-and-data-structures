#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in.tie(0)->sync_with_stdio(false);

    int n;
    in >> n;

    int count = 0, arc;
    for (int i = 0; i < n * n; i++)
    {
        in >> arc;

        if (arc == 1)
            count++;
    }

    if (count % 2 == 0)
        out << "YES\n";
    else
        out << "NO\n";

    return 0;
}