#include <bits/stdc++.h>
 
using namespace std;
using ll = unsigned long long;
 
ll Implementaion(vector<int> &array, int LeftBound, int MidPointer, int RightBound)
{
    int LeftBoundShift = 0, MidPointerShift = 0;
    ll inv_count = 0;
    vector<int> save(RightBound - LeftBound + 1);
 
    while (LeftBound + LeftBoundShift <= MidPointer - 1 && MidPointer + MidPointerShift <= RightBound)
        if (array[LeftBound + LeftBoundShift] <= array[MidPointer + MidPointerShift])
        {
            save[LeftBoundShift + MidPointerShift] = array[LeftBound + LeftBoundShift];
            LeftBoundShift++;
        }
        else
        {
            save[LeftBoundShift + MidPointerShift] = array[MidPointer + MidPointerShift];
            inv_count += MidPointer - LeftBound - LeftBoundShift;
            MidPointerShift++;
        }
 
    while (LeftBound + LeftBoundShift <= MidPointer - 1)
    {
        save[LeftBoundShift + MidPointerShift] = array[LeftBound + LeftBoundShift];
        LeftBoundShift++;
    }
 
    while (MidPointer + MidPointerShift <= RightBound)
    {
        save[LeftBoundShift + MidPointerShift] = array[MidPointer + MidPointerShift];
        MidPointerShift++;
    }
 
    for (int i = 0; i < MidPointerShift + LeftBoundShift; i++)
    {
        array[LeftBound + i] = save[i];
    }
 
    return inv_count;
}
 
ll Sort(vector<int> &array, int LeftBound, int RightBound, ll &inv_count)
{
    if (LeftBound < RightBound)
    {
        int MidPointer = (LeftBound + RightBound) / 2;
 
        Sort(array, LeftBound, MidPointer, inv_count);
        Sort(array, MidPointer + 1, RightBound, inv_count);
 
        inv_count += Implementaion(array, LeftBound, MidPointer + 1, RightBound);
    }
 
    return inv_count;
}
 
int main()
{
    freopen("inversions.in", "r", stdin);
    freopen("inversions.out", "w", stdout);
    int n;
 
    cin >> n;
 
    vector<int> input(n);
 
    for (int &x : input)
    {
        cin >> x;
    }
 
    ll counter = 0;
    
    Sort(input, 0, n - 1, counter);
    cout << counter << endl;
 
    return 0;
}