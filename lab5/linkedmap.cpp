#include <fstream>
#include <bits/stdc++.h>

using namespace std;

ifstream in("linkedmap.in");
ofstream out("linkedmap.out");

class linkednode
{
public:
    pair<string, string> ss;

    linkednode *next;
    linkednode *prev;

    linkednode(pair<string, string> ss, linkednode *prev, linkednode *next = nullptr)
    {
        this->ss = ss;
        this->prev = prev;
        this->next = next;
    }
};

class HashTable
{
    int bucket;

    list<linkednode> *table;

    linkednode *last_added_node, *before_last_added_node;

public:
    HashTable(int quantity);

    long long hash(string x)
    {
        int hash_key = 1e5 / 2;
        int power = 1;

        long long hash_value = 0;

        for (int i = 0; i < x.size(); i++)
        {
            hash_value = (((int)x[i] * power) + hash_value) % hash_key;
            power *= 2;
        }

        return (hash_value);
    }

    bool exists(string x);

    void get(string x);

    void insert(string key, string x);

    void erase(string key);

    void prev(string key);

    void next(string key);
};

HashTable::HashTable(int quantity)
{
    this->bucket = quantity;

    table = new list<linkednode>[bucket];

    this->last_added_node = nullptr;

    this->before_last_added_node = nullptr;
}

bool HashTable::exists(string x)
{
    long long index = hash(x);

    for (auto i : table[index])
        if (i.ss.first == x)
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

    for (auto i : table[index])
        if (i.ss.first == x)
        {
            out << i.ss.second << '\n';
            return;
        }
}

void HashTable::insert(string key, string x)
{
    long long index = hash(key);

    if (!exists(key))
    {
        linkednode *newnode = new linkednode({key, x}, last_added_node);

        table[index].push_back(*newnode);

        linkednode *last_pushed = &table[index].back();

        if (last_added_node != nullptr)
            last_added_node->next = last_pushed;

        last_added_node = last_pushed;

        last_pushed = nullptr;
        newnode = nullptr;
    }
    else
    {
        for (auto &i : table[index])
            if (i.ss.first == key)
            {
                i.ss.second = x;
                break;
            }
    }
}

void HashTable::erase(string key)
{
    if (!exists(key))
        return;

    long long index = hash(key);

    for (auto i = table[index].begin(); i != table[index].end(); i++)
        if (i->ss.first == key)
        {
            if (i->prev != nullptr)
            {
                i->prev->next = i->next;
            }

            if (i->next != nullptr)
            {
                i->next->prev = i->prev;
            }

            if (last_added_node->ss.first == i->ss.first)
            {
                last_added_node = i->prev;
            }

            table[index].erase(i);
            break;
        }
}

void HashTable::prev(string key)
{
    if (!exists(key))
    {
        out << "none\n";
        return;
    }

    long long index = hash(key);

    for (auto i : table[index])
        if (i.ss.first == key)
        {
            if (i.prev != nullptr)
                out << i.prev->ss.second << '\n';
            else
                out << "none\n";

            return;
        }
}

void HashTable::next(string key)
{
    if (!exists(key))
    {
        out << "none\n";
        return;
    }

    long long index = hash(key);

    for (auto i : table[index])
        if (i.ss.first == key)
        {
            if (i.next != nullptr)
                out << i.next->ss.second << '\n';
            else
                out << "none\n";

            return;
        }
}

int main()
{
    in.tie(NULL)->sync_with_stdio(NULL);

    string option, key, value;

    HashTable *ht = new HashTable(int(1e5) / 2);
    
    while (in >> option)
    {
        if (option == "put")
        {
            in >> key >> value;
            ht->insert(key, value);
        }
        else if (option == "delete")
        {
            in >> key;
            ht->erase(key);
        }
        else if (option == "get")
        {
            in >> key;
            ht->get(key);
        }
        else if (option == "prev")
        {
            in >> key;
            ht->prev(key);
        }
        else if (option == "next")
        {
            in >> key;
            ht->next(key);
        }
    }

    delete ht;
    return 0;
}