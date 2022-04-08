#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in.tie(0)->sync_with_stdio(false);

    unsigned n,m;
    in>>n>>m;

    vector<vector<int>>udg(n);

    for(int i=0;i<m;i++)
    {
        unsigned a,b;
        in>>a>>b;

        udg[a-1].push_back(b-1);
        udg[b-1].push_back(a-1);
    }

    for(auto &i:udg)
    {
        out<<i.size()<<' ';
    }

    return 0;
}