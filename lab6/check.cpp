#include <bits/stdc++.h>
#include <fstream>
 
using namespace std;
 
struct level_description
{
    int key;
    int leftson;
    int rightson;
};
 
bool check(vector<level_description> &nodes, int current_node_index, int min, int max)
{
    if (nodes.size()==0 || current_node_index==-1)
    return true;
 
    if (nodes[current_node_index].key <= min || nodes[current_node_index].key >= max)
    {
        return false;
    }
    else
    {
        return check(nodes, nodes[current_node_index].rightson, nodes[current_node_index].key, max) && check(nodes, nodes[current_node_index].leftson, min, nodes[current_node_index].key);
    }
}
 
int main()
{
    ifstream in("check.in");
    ofstream out("check.out");
    in.tie(NULL)->sync_with_stdio(NULL);
    out.tie(NULL)->sync_with_stdio(NULL);
 
    int n;
    in >> n;
 
    vector<level_description> nodes(n);
 
    for (int i = 0; i < n; ++i)
    {
        in >> nodes[i].key >> nodes[i].leftson >> nodes[i].rightson;
 
        nodes[i].leftson--;
        nodes[i].rightson--;
    }
    if (check(nodes, 0, INT_MIN, INT_MAX))
        out << "YES\n";
    else
        out << "NO\n";
 
    return 0;
}