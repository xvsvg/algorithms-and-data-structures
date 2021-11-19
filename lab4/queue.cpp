#include <fstream>
#include <cmath>
 
using namespace std;
 
template <typename yourtype>
class Queue
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
    node *tail;
    int size;
 
public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
 
    bool IsEmpty()
    {
        if (size == 0)
            return true;
        else
            return false;
    }
 
    void push(yourtype data)
    {
        node *temp = new node(data);
        if (size != 0)
        {
            tail->next = temp;
 
            tail = temp;
        }
        else
        {
            tail = temp;
 
            head = tail;
        }
         
        temp = nullptr;
 
        size++;
    }
    //1(head)->2->3
    yourtype pop()
    {
 
        if (this->head != nullptr)
        {
            node *temp = head;
 
            yourtype result = this->head->data;
 
            head = head->next;
 
            delete[] temp;
            temp = nullptr;
 
            size--;
 
            return result;
        }
    }
 
    ~Queue()
    {
        while (!IsEmpty())
            pop();
    }
};
 
int main()
{
    ifstream in("queue.in");
    ofstream out("queue.out");
 
    int n;
    in >> n;
 
    char query;
    Queue<int> queue;
    int number;
 
    in.tie(0)->sync_with_stdio(false);
 
    for (int i = 0; i < n; i++)
    {
        in >> query;
        if (query == '-')
            out << queue.pop() << endl;
 
        if (query == '+')
        {
            in >> number;
            queue.push(number);
        }
    }
 
    return 0;
}