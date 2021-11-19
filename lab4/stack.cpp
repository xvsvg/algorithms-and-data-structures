#include <fstream>
#include <cmath>
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
 
    ~Stack()
    {
        while (!IsEmpty())
            pop();
    }
};
 
int main()
{
    ifstream in("stack.in");
    ofstream out("stack.out");
 
    int n;
    in >> n;
 
    char query;
    Stack<int> stack;
    int number;
 
    in.tie(0)->sync_with_stdio(false);
 
    for (int i = 0; i < n; i++)
    {
        in >> query;
        if (query == '-')
            out << stack.pop() << endl;
 
        if (query == '+')
        {
            in >> number;
            stack.push(number);
        }
    }
 
    return 0;
}