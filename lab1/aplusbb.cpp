#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("aplusb.in");
    ofstream out("aplusb.out");

    long long a,b;

    in>>a>>b;
    out<<a+b*b<<endl;

    return 0;
}