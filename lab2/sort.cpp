#include <bits/stdc++.h>
 
using namespace std;
 
void sort(vector<int> &array, int LeftBound, int MidPointer, int RightBound)
{
    int LeftBoundShift = 0, MidPointerShift = 0;
    vector<int> FinalArray(RightBound - LeftBound + 1);
    while (LeftBound + LeftBoundShift <= MidPointer - 1 && MidPointer + MidPointerShift <= RightBound)
    {
        if (array[LeftBound + LeftBoundShift] <= array[MidPointer + MidPointerShift])
        {
            FinalArray[LeftBoundShift + MidPointerShift] = array[LeftBound + LeftBoundShift];
            LeftBoundShift++;
        }
        else
        {
            FinalArray[LeftBoundShift + MidPointerShift] = array[MidPointer + MidPointerShift];
            MidPointerShift++;
        }
    }
 
    while (LeftBound + LeftBoundShift <= MidPointer - 1)
    {
        FinalArray[LeftBoundShift + MidPointerShift] = array[LeftBound + LeftBoundShift];
        LeftBoundShift++;
    }
 
    while (MidPointer + MidPointerShift <= RightBound)
    {
        FinalArray[LeftBoundShift + MidPointerShift] = array[MidPointer + MidPointerShift];
        MidPointerShift++;
    }
 
    for (int i = 0; i < MidPointerShift + LeftBoundShift; i++)
    {
        array[LeftBound + i] = FinalArray[i];
    }
}
 
void DivideAndConquer(vector<int> &array, int LeftBound, int RightBound)
{
    if (RightBound > LeftBound)
    {
        int MidPointer = (LeftBound + RightBound) / 2;
 
        DivideAndConquer(array, LeftBound, MidPointer);
        DivideAndConquer(array, MidPointer + 1, RightBound);
 
        sort(array, LeftBound, MidPointer + 1, RightBound);
    }
    else
        return;
}
 
int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(NULL);
 
    int n;
 
    cin >> n;
 
    vector<int> input(n);
 
    for (int &e : input)
    {
        cin >> e;
    }
 
    DivideAndConquer(input, 0, n - 1);
 
    for (int e : input)
    {
        cout << e << ' ';
    }
 
    return 0;
}