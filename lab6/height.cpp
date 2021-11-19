#include <bits/stdc++.h>
#include <fstream>
 
using namespace std;
 
int get_height(vector<pair<int, int>> &nodes, int current_node_index)
{
    int height = 1;
    if (nodes[current_node_index].first != -1)
        height = max(height, get_height(nodes, nodes[current_node_index].first) + 1);
 
    if (nodes[current_node_index].second != -1)
        height = max(height, get_height(nodes, nodes[current_node_index].second) + 1);
 
    return height;
}
 
int main()
{
    ifstream in("height.in");
    ofstream out("height.out");
    in.tie(NULL)->sync_with_stdio(NULL);
    out.tie(NULL)->sync_with_stdio(NULL);
 
    int n;
    in >> n;
    vector<pair<int, int>> nodes(n);
 
    if (n == 0)
        out << "0\n";
    else
    {
        int leftson, rightson, parent;
        for (int i = 0; i < n; ++i)
        {
            in >> parent >> leftson >> rightson;
 
            nodes[i] = make_pair(--leftson, --rightson);
        }
 
        out << get_height(nodes, 0) << '\n';
    }
 
    return 0;
}