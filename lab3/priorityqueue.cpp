#include <bits/stdc++.h>
 
using namespace std;
 
ifstream in("priorityqueue.in");
ofstream out("priorityqueue.out");
 
class PriorityQueue
{
    int size = 0;
 
    int *array = new int[0];
    int *initialpos = new int[0];
 
public:
    int IsEmpty()
    {
        if (size == 0)
            return 1;
        else
            return 0;
    }
 
    void push(int x, int number_of_line)
    {
        int *ResizedArray = new int[size + 1];
        int *ResizedPos = new int[size + 1];
 
        memcpy(ResizedArray, this->array, size * sizeof(int));
        memcpy(ResizedPos, this->initialpos, size * sizeof(int));
 
        ResizedArray[size] = x;
        ResizedPos[size] = number_of_line;
 
        size++;
 
        int i = size - 1;
        while (i > 0 && ResizedArray[i] < ResizedArray[(i - 1) / 2])
        {
            swap(ResizedArray[i], ResizedArray[(i - 1) / 2]);
            swap(ResizedPos[i], ResizedPos[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
 
        delete[] array;
        delete[] initialpos;
 
        array = ResizedArray;
        initialpos = ResizedPos;
 
        ResizedArray = nullptr;
        ResizedPos = nullptr;
    }
 
    void extract_min()
    {
        if (IsEmpty())
        {
            out << '*' << endl;
             
            return;
        }
 
        int result;
 
        int *ResizedArray = new int[size - 1];
        int *ResizedPos = new int[size - 1];
 
        swap(this->array[0], this->array[size - 1]);
        swap(this->initialpos[0], this->initialpos[size - 1]);
        result = this->array[size - 1];
        size--;
 
        memcpy(ResizedArray, this->array, size * sizeof(int));
        memcpy(ResizedPos, this->initialpos, size * sizeof(int));
 
        int curpos = 0;
        while (true)
        {
            int savepos = curpos;
 
            if (2 * savepos + 1 <= size - 1)
                if (ResizedArray[curpos] > ResizedArray[2 * savepos + 1])
                    curpos = 2 * savepos + 1;
 
            if (2 * savepos + 2 <= size - 1)
                if (ResizedArray[curpos] > ResizedArray[2 * savepos + 2])
                    curpos = 2 * savepos + 2;
 
            if (curpos == savepos)
                break;
            else
            {
                swap(ResizedArray[curpos], ResizedArray[savepos]);
                swap(ResizedPos[curpos], ResizedPos[savepos]);
            }
        }
        delete[] array;
        delete[] initialpos;
 
        array = ResizedArray;
        initialpos = ResizedPos;
 
        ResizedArray = nullptr;
        ResizedPos = nullptr;
 
        out << result << endl;
 
        return;
    }
 
    void decrease_key(int idx, int key)
    {
        int i = 0;
        for (i; i < size; i++)
            if (this->initialpos[i] == idx)
            {
                this->array[i] = key;
                break;
            }
        int j = i;
        while (j > 0 && array[j] < array[(j - 1) / 2])
        {
            swap(this->array[j], this->array[(j - 1) / 2]);
            swap(this->initialpos[j], this->initialpos[(j - 1) / 2]);
            j = (j - 1) / 2;
        }
    }
 
    ~PriorityQueue()
    {
        delete[] array;
        array = nullptr;
 
        delete[] initialpos;
        initialpos = nullptr;
    }
};
 
int main()
{
    string str;
 
    int number, linecounter=1;
 
    in.tie(0)->sync_with_stdio(0);
 
    int key1, key2;
 
    PriorityQueue queue;
 
    while (in >> str)
    {
        if (str == "push")
        {
            in >> number;
            queue.push(number, linecounter);
        }
 
        else if (str == "extract-min")
        {
            queue.extract_min();
        }
 
        else if (str == "decrease-key")
        {
            in >> key1 >> key2;
            queue.decrease_key(key1, key2);
        }
        linecounter++;
    }
 
    return 0;
}