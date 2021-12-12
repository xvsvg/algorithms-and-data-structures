#include <bits/stdc++.h>
#include <fstream>

using namespace std;

const int SETSIZE = 103;
const int MAPSIZE = 50001;

ifstream in("multimap.in");
ofstream out("multimap.out");

struct linkednode
{
    string key;
    linkednode *prev;
    linkednode *next;
};

class hash_set
{
private:
    list<linkednode> *set_table;
    linkednode *last_added_node = nullptr;
    int size = 0;

public:
    hash_set()
    {
        set_table = new list<linkednode>[SETSIZE];
    }

    int hash(string value);

    void put(string value);

    void erase(string value);

    int getsize()
    {
        return size;
    }

    void deleteall()
    {
        last_added_node = nullptr;
        size = 0;
        set_table = new list<linkednode>[SETSIZE];
    }
    linkednode *get_last_node()
    {
        return last_added_node;
    }
};

int hash_set::hash(string value)
{
    int hash = 5381;
    for (int i = 0; i < value.length(); ++i)
    {
        hash = (((hash << 5) + hash) + int(value[i])) % SETSIZE;
    }
    return hash;
}

void hash_set::put(string value)
{
    int index = hash(value);
    for (auto i = set_table[index].begin(); i != set_table[index].end(); i++)
    {
        if (i->key == value)
        {
            return;
        }
    }
    linkednode t = {value, last_added_node, nullptr};
    set_table[index].push_back(t);
    linkednode *check = &set_table[index].back();
    if (last_added_node != 0)
    {
        last_added_node->next = check;
    }
    last_added_node = check;
    size++;
}

void hash_set::erase(string value)
{
    int index = hash(value);
    for (auto i = set_table[index].begin(); i != set_table[index].end(); i++)
    {
        if (i->key == value)
        {
            if (i->prev != 0)
            {
                i->prev->next = i->next;
            }
            if (i->next != 0)
            {
                i->next->prev = i->prev;
            }
            if (i->key == last_added_node->key)
            {
                last_added_node = i->prev;
            }
            set_table[index].erase(i);
            size--;
            return;
        }
    }
}

struct mapnode
{
    string key;
    hash_set *set_table;
};

class multi_map
{
private:
    list<mapnode> map_table[MAPSIZE];

public:
    int hash(string key);

    void get(string key);

    void put(string key, string value);

    void erase(string key, string value);

    void deleteall(string key);
};

int multi_map::hash(string key)
{
    int hash = 5381;
    for (int i = 0; i < key.length(); ++i)
    {
        hash = (((hash << 5) + hash) + int(key[i])) % MAPSIZE;
    }
    return hash;
}

void multi_map::get(string key)
{
    int index = hash(key);
    for (auto i = map_table[index].begin(); i != map_table[index].end(); i++)
    {
        if (i->key == key)
        {
            out << i->set_table->getsize() << ' ';
            linkednode *iterator = i->set_table->get_last_node();

            while (iterator != nullptr)
            {
                out << iterator->key << ' ';
                iterator = iterator->prev;
            }
            out << '\n';
            return;
        }
    }
    out << 0 << '\n';
}

void multi_map::put(string key, string value)
{
    int index = hash(key);
    for (auto i = map_table[index].begin(); i != map_table[index].end(); i++)
    {
        if (i->key == key)
        {
            i->set_table->put(value);
            return;
        }
    }
    mapnode t;
    t.key = key;
    hash_set *vls = new hash_set;
    vls->put(value);
    t.set_table = vls;

    map_table[index].push_back(t);
}

void multi_map::erase(string key, string value)
{
    int index = hash(key);
    for (auto i = map_table[index].begin(); i != map_table[index].end(); i++)
    {
        if (i->key == key)
        {
            i->set_table->erase(value);
        }
    }
}

void multi_map::deleteall(string key)
{
    int index = hash(key);
    for (auto i = map_table[index].begin(); i != map_table[index].end(); i++)
    {
        if (i->key == key)
        {
            i->set_table->deleteall();
        }
    }
}

int main()
{
    multi_map mm;
    string command;
    string key, value;
    while (in >> command)
    {
        if (command == "put")
        {
            in >> key >> value;
            mm.put(key, value);
        }
        else if (command == "delete")
        {
            in >> key >> value;
            mm.erase(key, value);
        }
        else if (command == "deleteall")
        {
            in >> key;
            mm.deleteall(key);
        }
        else if (command == "get")
        {
            in >> key;
            mm.get(key);
        }
    }
}
