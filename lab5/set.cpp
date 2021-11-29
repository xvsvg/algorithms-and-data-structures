#include <bits/stdc++.h>
#include <fstream>

using namespace std;

template <typename type>
class HashTable
{
    int bucket;

    list<type> *table;

public:
    HashTable(int quantity);

    type hash(type x)
    {
        return abs(x) % bucket;
    }

    bool exists(type x);

    void insert(type x);

    void erase(type x);
};

template <typename type>
HashTable<type>::HashTable(int quantity)
{
    this->bucket = quantity;

    table = new list<type>[bucket];
}

template <typename type>
bool HashTable<type>::exists(type x)
{
    int index = hash(x);

    list<int>::iterator i;
    
    for (i = table[index].begin(); i != table[index].end(); i++)
        if (*i == x)
            return true;

    return false;
}

template <typename type>
void HashTable<type>::insert(type x)
{
    if (exists(x))
        return;

    int index = hash(x);

    table[index].push_back(x);
}

template <typename type>
void HashTable<type>::erase(type x)
{
    if (!exists(x))
        return;

    int index = hash(x);

    list<int>::iterator i;

    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if (*i == x)
            break;
    }

    if (i != table[index].end())
        table[index].erase(i);
}

int main()
{
    ifstream in("set.in");
    ofstream out("set.out");

    in.tie(NULL)->sync_with_stdio(NULL);

    string input;
    int number;

    HashTable<int> ht(int(1e6)/2);

    while (in >> input)
    {
        in >> number;

        if (input == "insert")
        {
            ht.insert(number);
        }
        else if (input == "delete")
        {
            ht.erase(number);
        }
        else if (input == "exists")
        {
            (ht.exists(number)) ? (out<<"true\n") : (out<<"false\n");
        }
    }

    return 0;
}
