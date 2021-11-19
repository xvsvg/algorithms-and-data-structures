#include <bits/stdc++.h>
#include <fstream>
 
using namespace std;
 
const int MODULE = 65536;
 
int goto_label(vector<pair<string, int>> &labels, string label)
{
    for (int i = 0; i < labels.size(); i++)
    {
        if (labels[i].first == label)
            return labels[i].second;
    }
}
 
int main()
{
    ifstream in("quack.in");
    ofstream out("quack.out");
 
    vector<string> commands;
    vector<int> registers(26);
    vector<pair<string, int>> labels;
    queue<int> quack_queue;
 
    string command, label;
 
    char register_name, register_name1;
 
    while (in >> command)
    {
        commands.push_back(command);
    }
 
    for (int i = 0; i < commands.size(); i++)
    {
        if (commands[i][0] == ':')
            labels.push_back(make_pair(commands[i].substr(1), i));
    }
 
    int x, y;
 
    for (int i = 0; i < commands.size(); i++)
    {
        command = commands[i];
 
        switch (command[0])
        {
        case '+':
            x = quack_queue.front();
            quack_queue.pop();
 
            y = quack_queue.front();
            quack_queue.pop();
 
            quack_queue.push((x + y) & (MODULE - 1));
            break;
 
        case '-':
            x = quack_queue.front();
            quack_queue.pop();
 
            y = quack_queue.front();
            quack_queue.pop();
 
            quack_queue.push((x - y) & (MODULE - 1));
            break;
 
        case '*':
            x = quack_queue.front();
            quack_queue.pop();
 
            y = quack_queue.front();
            quack_queue.pop();
 
            quack_queue.push((x * y) & (MODULE - 1));
            break;
 
        case '/':
            x = quack_queue.front();
            quack_queue.pop();
 
            y = quack_queue.front();
            quack_queue.pop();
 
            if (y == 0)
                quack_queue.push(0);
            else
                quack_queue.push((x / y) & (MODULE - 1));
            break;
 
        case '%':
            x = quack_queue.front();
            quack_queue.pop();
 
            y = quack_queue.front();
            quack_queue.pop();
 
            if (y == 0)
                quack_queue.push(0);
            else
                quack_queue.push((x % y) & (MODULE - 1));
            break;
 
        case '>':
            x = quack_queue.front();
            quack_queue.pop();
 
            register_name = command[1];
            registers[register_name - 'a'] = x;
            break;
 
        case '<':
            register_name = command[1];
            x = registers[register_name - 'a'];
 
            quack_queue.push(x);
 
            break;
 
        case 'P':
            if (command.size() == 1)
            {
                x = quack_queue.front();
                quack_queue.pop();
                out << x << '\n';
            }
            else
            {
                register_name = command[1];
                x = registers[register_name - 'a'];
 
                out << x << '\n';
            }
            break;
 
        case 'C':
            if (command.size() == 1)
            {
                x = quack_queue.front();
                quack_queue.pop();
                out << char(x % 256);
            }
            else
            {
                register_name = command[1];
                x = registers[register_name - 'a'];
 
                out << char(x % 256);
            }
            break;
 
        case ':':
            break;
 
        case 'J':
            label = commands[i].substr(1);
            i = goto_label(labels, label);
            break;
 
        case 'Z':
            label = commands[i].substr(2);
 
            register_name = command[1];
 
            x = registers[register_name - 'a'];
 
            if (x == 0)
                i = goto_label(labels, label);
 
            break;
 
        case 'E':
            register_name = command[1];
            register_name1 = command[2];
            label = commands[i].substr(3);
 
            x = registers[register_name - 'a'];
            y = registers[register_name1 - 'a'];
            if (x == y)
                i = goto_label(labels, label);
            break;
 
        case 'G':
            register_name = command[1];
            register_name1 = command[2];
            label = commands[i].substr(3);
 
            x = registers[register_name - 'a'];
            y = registers[register_name1 - 'a'];
            if (x > y)
                i = goto_label(labels, label);
            break;
 
        case 'Q':
            return 0;
            break;
 
        default:
            quack_queue.push(atoi(command.c_str()));
            break;
        }
    }
 
    return 0;
}