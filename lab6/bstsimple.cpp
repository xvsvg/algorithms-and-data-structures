#include <fstream>
#include <bits/stdc++.h>
 
using namespace std;
 
ifstream in("bstsimple.in");
ofstream out("bstsimple.out");
 
template <typename type>
class Binary_Search_Tree
{
    class node
    {
    public:
        type val;
 
        int val_count;
 
        node *parent, *leftson, *rightson;
 
        node(type val = type(), node *parent = nullptr, node *leftson = nullptr, node *rightson = nullptr)
        {
            this->val = val;
 
            this->parent = parent;
 
            this->leftson = leftson;
 
            this->rightson = rightson;
        }
    };
 
    node *tree_root;
 
public:
    Binary_Search_Tree();
 
    node *get(type x);
 
    void insert(type x);
 
    void erase(type x);
 
    bool exists(type x);
 
    type next(type x);
 
    type prev(type x);
};
 
template <typename type>
Binary_Search_Tree<type>::Binary_Search_Tree()
{
    this->tree_root = nullptr;
}
 
template <typename type>
bool Binary_Search_Tree<type>::exists(type x)
{
    node *current_node = tree_root;
 
    while (current_node != nullptr && x != current_node->val)
    {
        if (current_node->val < x)
            if (current_node->rightson != nullptr)
                current_node = current_node->rightson;
            else
                break;
 
        if (current_node->val > x)
            if (current_node->leftson != nullptr)
                current_node = current_node->leftson;
            else
                break;
    }
 
    if (current_node != nullptr)
    {
        if (current_node->val == x)
        {
            current_node = nullptr;
            return true;
        }
        else
        {
            current_node = nullptr;
            return false;
        }
    }
    else
        return false;
}
 
template <typename type>
void Binary_Search_Tree<type>::insert(type x)
{
    if (tree_root == nullptr)
    {
        tree_root = new node(x, tree_root);
        return;
    }
 
    if (exists(x))
        return;
 
    node *current_node = tree_root;
 
    while (current_node != nullptr)
    {
        if (current_node->val < x)
            if (current_node->rightson != nullptr)
                current_node = current_node->rightson;
            else
            {
                node *newnode = new node(x, current_node);
 
                current_node->rightson = newnode;
 
                newnode = nullptr;
 
                break;
            }
 
        if (current_node->val > x)
            if (current_node->leftson != nullptr)
                current_node = current_node->leftson;
            else
            {
                node *newnode = new node(x, current_node);
 
                current_node->leftson = newnode;
 
                newnode = nullptr;
 
                break;
            }
    }
}
 
template <typename type>
typename Binary_Search_Tree<type>::node *Binary_Search_Tree<type>::get(type x)
{
    node *current_node = tree_root;
 
    while (current_node != nullptr && current_node->val != x)
    {
        if (current_node->val < x)
            if (current_node->rightson != nullptr)
                current_node = current_node->rightson;
            else
                break;
 
        if (current_node->val > x)
            if (current_node->leftson != nullptr)
                current_node = current_node->leftson;
            else
                break;
    }
 
    if (current_node != nullptr)
    {
        if (current_node->val == x)
            return current_node;
        else
            return nullptr;
    }
    else
        return nullptr;
}
 
template <typename type>
type Binary_Search_Tree<type>::next(type x)
{
    node *current_node = tree_root;
 
    while (current_node != nullptr)
    {
        if (x < current_node->val)
        {
            if (current_node->leftson == nullptr)
                break;
 
            current_node = current_node->leftson;
        }
        else
        {
            if (current_node->rightson == nullptr)
                break;
 
            current_node = current_node->rightson;
        }
    }
 
    while (current_node != nullptr && current_node->val <= x)
    {
        current_node = current_node->parent;
    }
 
    if (current_node != nullptr)
        return current_node->val;
 
    return (int)(1e9) + 1;
}
 
template <typename type>
type Binary_Search_Tree<type>::prev(type x)
{
    node *current_node = tree_root;
 
    while (current_node != nullptr)
    {
        if (x <= current_node->val)
        {
            if (current_node->leftson == nullptr)
                break;
 
            current_node = current_node->leftson;
        }
        else
        {
            if (current_node->rightson == nullptr)
                break;
 
            current_node = current_node->rightson;
        }
    }
 
    while (current_node != nullptr && current_node->val >= x)
    {
        current_node = current_node->parent;
    }
 
    if (current_node != nullptr)
        return current_node->val;
 
    return (int)(1e9) + 1;
}
 
template <typename type>
void Binary_Search_Tree<type>::erase(type x)
{
    if (!exists(x))
        return;
 
    node *for_removing = get(x);
 
    if (for_removing->leftson == nullptr && for_removing->rightson == nullptr)
    {
        if (for_removing->parent != nullptr)
        {
            if (for_removing->parent->leftson == get(x))
            {
                for_removing->parent->leftson = nullptr;
                delete for_removing;
            }
            else if (for_removing->parent->rightson == get(x))
            {
                for_removing->parent->rightson = nullptr;
                delete for_removing;
            }
        }
        else
        {
            delete tree_root;
            tree_root = nullptr;
        }
    }
    else if (for_removing->leftson == nullptr || for_removing->rightson == nullptr)
    {
        if (for_removing->leftson != nullptr)
        {
            if (for_removing->parent != nullptr)
            {
                if (for_removing->parent->leftson == get(x))
                {
                    for_removing->parent->leftson = for_removing->leftson;
 
                    for_removing->leftson->parent = for_removing->parent;
 
                    delete for_removing;
                }
                else if (for_removing->parent->rightson == get(x))
                {
                    for_removing->parent->rightson = for_removing->leftson;
 
                    for_removing->leftson->parent = for_removing->parent;
 
                    delete for_removing;
                }
            }
            else
            {
                for_removing->leftson->parent = for_removing->parent;
                tree_root = for_removing->leftson;
                delete for_removing;
            }
        }
        else if (for_removing->rightson != nullptr)
        {
            if (for_removing->parent != nullptr)
            {
                if (for_removing->parent->leftson == get(x))
                {
                    for_removing->parent->leftson = for_removing->rightson;
 
                    for_removing->rightson->parent = for_removing->parent;
 
                    delete for_removing;
                }
                else if (for_removing->parent->rightson == get(x))
                {
                    for_removing->parent->rightson = for_removing->rightson;
 
                    for_removing->rightson->parent = for_removing->parent;
 
                    delete for_removing;
                }
            }
            else
            {
                for_removing->rightson->parent = for_removing->parent;
                tree_root = for_removing->rightson;
                delete for_removing;
            }
        }
    }
    else
    {
        node *successor = get(next(x));
 
        if (successor == nullptr)
            successor = tree_root->rightson;
 
        for_removing->val = successor->val;
 
        if (successor->parent->leftson == successor)
        {
            successor->parent->leftson = successor->rightson;
            if (successor->rightson != nullptr)
                successor->rightson->parent = successor->parent;
            delete successor;
        }
        else
        {
            successor->parent->rightson = successor->rightson;
            if (successor->rightson != nullptr)
                successor->rightson->parent = successor->parent;
            delete successor;
        }
        successor = nullptr;
    }
    for_removing = nullptr;
}
 
int main()
{
    in.tie(NULL)->sync_with_stdio(false);
    out.tie(NULL)->sync_with_stdio(false);
 
    string command;
    int number;
 
    Binary_Search_Tree<int> bst;
 
    while (in >> command)
    {
        in >> number;
 
        if (command == "insert")
            bst.insert(number);
 
        if (command == "exists")
            (bst.exists(number) == true) ? (out << "true\n") : (out << "false\n");
 
        if (command == "next")
            if (bst.next(number) != (int)(1e9 + 1))
                out << bst.next(number) << '\n';
            else
                out << "none\n";
 
        if (command == "prev")
            if (bst.prev(number) != (int)(1e9 + 1))
                out << bst.prev(number) << '\n';
            else
                out << "none\n";
 
        if (command == "delete")
            bst.erase(number);
    }
 
    return 0;
}