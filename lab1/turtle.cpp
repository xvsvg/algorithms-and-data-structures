#include <bits/stdc++.h>
#include <fstream>

using namespace std;
 
int main()
{
    ifstream in("turtle.in");
    ofstream out("turtle.out");

    int h, w;
    in >> h >> w;
    vector<vector<int>> field(h + 2, vector<int>(w + 2, 0));
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            in >> field[i][j];
        }
    }
    for (int i = h - 1; i >= 1; i--)
    {
        field[i][1] += field[i + 1][1];
    }
    for (int j = 2; j <= w; j++)
    {
        field[h][j] += field[h][j - 1];
    }
    for (int j = 2; j <= w; j++)
    {
        for (int i = h - 1; i >= 1; i--)
        {
            field[i][j] += max(field[i + 1][j], field[i][j - 1]);
        }
    }

    out << field[1][w]<<endl;
    return 0;
}