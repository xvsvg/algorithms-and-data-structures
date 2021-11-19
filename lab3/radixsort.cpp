#include <bits/stdc++.h>
 
using namespace std;
 
//rows = строки
//cols = столбцы
 
void radixsort(vector<string> &array, int length, int phase)
{
 
    for (int i = 0; i < phase; i++) //sort till i!=phase
    {
        vector<int> ArrayOfFrequency(26); //frequent array
 
        vector<vector<string>> SortResult(26); //rows = letters, cols = words
 
        for (int k = 0; k < array.size(); k++) //for n strings do:
        {
            ArrayOfFrequency[array[k][length - i - 1] - 'a']++;             //count how much strings have same char on length-i position
            SortResult[array[k][length - i - 1] - 'a'].push_back(array[k]); //remember that strings
        }
 
        int pointer = 0;
 
        for (int k = 0; k < 26; k++) //for n strings do:
        {
            if (ArrayOfFrequency[k] != 0) //if letter appears somewhere in given strings
            {
                for (int j = 0; j < ArrayOfFrequency[k]; j++) //put strings with same chars in given array
                    array[pointer++] = SortResult[k][j];
            }
        }
    }
    for (auto str : array)
        cout << str << endl;
}
 
// 3 3 2
// bbb
// aba
// baa
 
int main()
{
    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);
 
    int n, m, k, phase = 0;
 
    cin >> n >> m >> k;
 
    vector<string> array(n);
 
    for (auto &e : array)
        cin >> e;
 
    radixsort(array, m, k);
}