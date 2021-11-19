#include <bits/stdc++.h>
 
using namespace std;
 
struct Racer
{
    string _Country;
    string _SecondName;
};
 
void Implementaion(vector<Racer> &array, int LeftBound, int MidPointer, int RightBound)
{
    int LeftBoundShift = 0, MidPointerShift = 0;
 
    vector<Racer> save(RightBound - LeftBound + 1);
 
    while (LeftBound + LeftBoundShift <= MidPointer - 1 && MidPointer + MidPointerShift <= RightBound)
        if (array[LeftBound + LeftBoundShift]._Country < array[MidPointer + MidPointerShift]._Country)
        {
            save[LeftBoundShift + MidPointerShift]._Country = array[LeftBound + LeftBoundShift]._Country;
            save[LeftBoundShift + MidPointerShift]._SecondName = array[LeftBound + LeftBoundShift]._SecondName;
 
            LeftBoundShift++;
        }
        else
        {
            save[LeftBoundShift + MidPointerShift]._Country = array[MidPointer + MidPointerShift]._Country;
 
            if (array[LeftBound + LeftBoundShift]._Country > array[MidPointer + MidPointerShift]._Country)
            {
                save[LeftBoundShift + MidPointerShift]._SecondName = array[MidPointer + MidPointerShift]._SecondName;
                MidPointerShift++;
            }
            else
            {
                save[LeftBoundShift + MidPointerShift]._SecondName = array[LeftBound + LeftBoundShift]._SecondName;
                LeftBoundShift++;
            }
        }
 
    while (LeftBound + LeftBoundShift <= MidPointer - 1)
    {
        save[LeftBoundShift + MidPointerShift]._Country = array[LeftBound + LeftBoundShift]._Country;
        save[LeftBoundShift + MidPointerShift]._SecondName = array[LeftBound + LeftBoundShift]._SecondName;
 
        LeftBoundShift++;
    }
 
    while (MidPointer + MidPointerShift <= RightBound)
    {
        save[LeftBoundShift + MidPointerShift]._Country = array[MidPointer + MidPointerShift]._Country;
        save[LeftBoundShift + MidPointerShift]._SecondName = array[MidPointer + MidPointerShift]._SecondName;
 
        MidPointerShift++;
    }
 
    for (int i = 0; i < MidPointerShift + LeftBoundShift; i++)
    {
        array[LeftBound + i]._Country = save[i]._Country;
        array[LeftBound + i]._SecondName = save[i]._SecondName;
    }
}
 
void Sort(vector<Racer> &array, int LeftBound, int RightBound)
{
    if (RightBound > LeftBound)
    {
        int MidPointer = (RightBound + LeftBound) / 2;
 
        Sort(array, LeftBound, MidPointer);
        Sort(array, MidPointer + 1, RightBound);
 
        Implementaion(array, LeftBound, MidPointer + 1, RightBound);
    }
}
 
int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int n;
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
 
    cin >> n;
 
    vector<Racer> RacerData(n);
 
    for (auto &e : RacerData)
    {
        cin >> e._Country;
        cin >> e._SecondName;
    }
 
    Sort(RacerData, 0, n - 1);
 
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            cout << "=== " << RacerData[i]._Country << " ===" << endl;
            cout << RacerData[i]._SecondName << endl;
        }
        else
        {
            if (RacerData[i - 1]._Country == RacerData[i]._Country)
                cout << RacerData[i]._SecondName << endl;
            else
            {
                cout << "=== " << RacerData[i]._Country << " ===" << endl;
                cout << RacerData[i]._SecondName << endl;
            }
        }
    }
    return 0;
}