#include <fstream>
#include <iostream>
 
using namespace std;
 
template <typename yourtype>
class Stack
{
    class node
    {
    public:
        node *next;
        yourtype data;
 
        node(yourtype data = yourtype(), node *next = nullptr)
        {
            this->data = data;
            this->next = next;
        }
    };
 
    node *head;
 
public:
    Stack()
    {
        head = nullptr;
    }
 
    bool IsEmpty()
    {
        if (head == nullptr)
            return true;
        else
            return false;
    }
 
    void push(yourtype data)
    {
        if (IsEmpty())
            this->head = new node(data);
 
        else
        {
            node *temp = this->head;
 
            this->head = new node(data, temp);
 
            temp = nullptr;
        }
    }
 
    yourtype pop()
    {
 
        if (this->head != nullptr)
        {
            node *temp = head;
 
            yourtype result = this->head->data;
 
            head = head->next;
 
            delete[] temp;
            temp = nullptr;
 
            return result;
        }
    }
 
    yourtype checkpop()
    {
        return head->data;
    }
 
    ~Stack()
    {
        while (!IsEmpty())
            pop();
    }
};
 
int main()
{
    ifstream in("brackets.in");
    ofstream out("brackets.out");
 
    in.tie(NULL)->sync_with_stdio(NULL);
 
    string str;
 
    while (in >> str)
    {
        bool IsExecuted = false;
 
        Stack<char> stack;
 
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '(')
            {
                stack.push(str[i]);
            }
 
            else if (str[i] == '[')
            {
                stack.push(str[i]);
            }
 
            else if (stack.IsEmpty())
            {
                out << "NO" << endl;
                IsExecuted = true;
                break;
            }
 
            else if (str[i] == ')' && stack.checkpop() == '(')
            {
                stack.pop();
            }
 
            else if (str[i] == ']' && stack.checkpop() == '[')
            {
                stack.pop();
            }
 
            else if (!(str[i] == ']' && stack.checkpop() == '['))
            {
                stack.push(str[i]);
            }
 
            else if (!(str[i] == ')' && stack.checkpop() == '('))
            {
                stack.push(str[i]);
            }
        }
 
        if (!IsExecuted)
            if (stack.IsEmpty())
                out << "YES" << endl;
            else
                out << "NO" << endl;
    }
 
    return 0;
}