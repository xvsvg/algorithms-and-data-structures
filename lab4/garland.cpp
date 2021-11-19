#include <fstream>
#include <bits/stdc++.h>
 
using ld = long double;
using namespace std;
 
double bsearch(vector<ld> &array, int QuantOfLamps)
{
    ld l = 0;
    ld r = array[0];
 
    ld eps = 1e-9;
 
    while (r - l > eps)
    {
        array[1] = (ld)(r + l) / 2;
        bool IsNegative = 0;
 
        for (int i = 2; i < QuantOfLamps; i++)
        {
            array[i] = 2 * array[i - 1] - array[i - 2] + 2;
 
            if (array[i] < 0)
            {
                IsNegative = 1;
                break;
            }
        }
 
        if (IsNegative)
            l = array[1];
 
        else
            r = array[1];
    }
 
    return array[QuantOfLamps - 1];
}
 
int main()
{
    ifstream in("garland.in");
    ofstream out("garland.out");
 
    in.tie(NULL)->sync_with_stdio(NULL);
 
    int n;
    ld a;
    in >> n >> a;
 
    vector<ld> hights(n);
 
    hights[0] = a;
 
    out << setprecision(2) << fixed << bsearch(hights, n);
 
    return 0;
}