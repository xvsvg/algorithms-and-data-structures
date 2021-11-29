#include <fstream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("map.in");
ofstream out("map.out");

class HashTable
{
    int bucket;

    list<pair<string, string>> *table;

public:
    HashTable(int quantity);

    long long hash(string x)
    {
        int hash_key = 1e5 / 2;

        long long hash_value = 0;

        short prime_numbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

        for (int i = 0; i < x.size(); i++)
        {
            hash_value += int(x[i]) * prime_numbers[19-i];
        }

        return (hash_value) % hash_key;
    }

    bool exists(string x);

    void get(string x);

    void insert(string key, string x);

    void erase(string key);
};

HashTable::HashTable(int quantity)
{
    this->bucket = quantity;

    table = new list<pair<string, string>>[bucket];
}

bool HashTable::exists(string x)
{
    long long index = hash(x);

    list<pair<string, string>>::iterator i;

    for (i = table[index].begin(); i != table[index].end(); i++)
        if (i->first == x)
            return true;

    return false;
}

void HashTable::get(string x)
{
    if (!exists(x))
    {
        out << "none\n";
        return;
    }

    long long index = hash(x);

    list<pair<string, string>>::iterator i;

    for (i = table[index].begin(); i != table[index].end(); i++)
        if (i->first == x)
        {
            out << i->second << '\n';
            return;
        }
}

void HashTable::insert(string key, string x)
{
    if (exists(key))
    {
        long long index = hash(key);

        list<pair<string, string>>::iterator i;

        for (i = table[index].begin(); i != table[index].end(); i++)
            if (i->first == key)
                i->second = x;

        return;
    }

    long long index = hash(key);

    table[index].push_back(make_pair(key, x));
}

void HashTable::erase(string key)
{
    if (!exists(key))
        return;

    long long index = hash(key);

    list<pair<string, string>>::iterator i;

    for (i = table[index].begin(); i != table[index].end(); i++)
    {
        if (i->first == key)
            break;
    }

    if (i != table[index].end())
        table[index].erase(i);
}

int main()
{
    in.tie(NULL)->sync_with_stdio(NULL);

    string option, key, value;

    HashTable ht(int(1e5) / 2);

    while (in >> option)
    {

        if (option == "put")
        {
            in >> key >> value;
            ht.insert(key, value);
        }
        else if (option == "delete")
        {
            in >> key;
            ht.erase(key);
        }
        else if (option == "get")
        {
            in >> key;
            ht.get(key);
        }
    }
}