#include <bits/stdc++.h>
 
using namespace std;
 
void insert(int value, vector<int> &array)
{
  array.push_back(value);
 
  int curpos = array.size() - 1;
 
  while (curpos > 0 && array[curpos] < array[(curpos - 1) / 2])
  {
    swap(array[curpos], array[(curpos - 1) / 2]);
    curpos = (curpos - 1) / 2;
  }
}
 
int remove_min(vector<int> &arr)
{
  swap(arr[0], arr[arr.size() - 1]);
 
  int curpos = 0;
 
  int res = arr[arr.size() - 1];
 
  arr.resize(arr.size() - 1);
 
  while (true)
  {
    if (arr.size() == 0)
      break;
    int savepos = curpos;
 
    if (2 * savepos + 1 <= arr.size() - 1)
      if (arr[curpos] > arr[2 * savepos + 1])
        curpos = 2 * savepos + 1;
 
    if (2 * savepos + 2 <= arr.size() - 1)
      if (arr[curpos] > arr[2 * savepos + 2])
        curpos = 2 * savepos + 2;
 
    if (curpos == savepos)
      break;
    else
      swap(arr[curpos], arr[savepos]);
  }
  return res;
}
 
int main()
{
  freopen("sort.in", "r", stdin);
  freopen("sort.out", "w", stdout);
 
  vector<int> array;
 
  int n, a;
 
  cin >> n;
 
  for (size_t i = 0; i < n; i++)
  {
    cin >> a;
    array.push_back(a);
  }
 
  vector<int> heap;
 
  for (size_t i = 0; i < n; i++)
  {
    insert(array[i], heap);
  }
 
  for (size_t i = 0; i < n; i++)
  {
    int x = remove_min(heap);
 
    array[i] = x;
 
    cout << array[i] << ' ';
  }
 
  return 0;
}