#include <fstream>
#include <cmath>
 
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
 
    void plus()
    {
 
        if (this->head != nullptr)
        {
            node *temp = head;
 
            yourtype save = this->head->data;
 
            head = head->next;
 
            delete[] temp;
            temp = nullptr;
 
            head->data += save;
        }
    }
 
    void minus()
    {
 
        if (this->head != nullptr)
        {
            node *temp = head;
 
            yourtype save = this->head->data;
 
            head = head->next;
 
            delete[] temp;
            temp = nullptr;
 
            head->data -= save;
        }
    }
 
    void mult()
    {
 
        if (this->head != nullptr)
        {
            node *temp = head;
 
            yourtype save = this->head->data;
 
            head = head->next;
 
            delete[] temp;
            temp = nullptr;
 
            head->data *= save;
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
    ifstream in("postfix.in");
    ofstream out("postfix.out");
 
    in.tie(NULL)->sync_with_stdio(NULL);
 
    string str;
    getline(in, str, '\n');
 
    Stack<int> stack;
 
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '+')
            stack.plus();
 
        else if (str[i] == '-')
            stack.minus();
 
        else if (str[i] == '*')
            stack.mult();
 
        else if (str[i] != ' ')
            stack.push(str[i] - '0');
    }
    out << stack.pop() << endl;
 
    return 0;
}