#include <iostream>
using namespace std;

struct Node
{
    int severity;
    string name;
    int ID;
    string Arrival;
    Node *next;
};

class Patient
{
private:
    Node *head = new Node;

public:
    Patient()
    {
        head = NULL;
    }
    void insertAtFront(int s, string n, int id, string a)
    {
        Node *start = new Node();
        start->Arrival = a;
        start->ID = id;
        start->name = n;
        start->severity = s;
        start->next = head;
        head = start;
    }
    void insertAtEnd(int s, string n, int id, string a)
    {
        Node *end = new Node();
        Node *temp;
        temp = head;
        end->Arrival = a;
        end->ID = id;
        end->name = n;
        end->severity = s;
        while (temp)
        {
            temp = temp->next;
        }
        if (!head)
        {
            head = end;
        }
        temp = end;
    }
    void searching(int id)
    {
        Node *node;
        node = head;
        int pos = 0;
        while (node)
        {
            pos++;
            if (node->ID == id)
            {
                cout << "Node fount at position " << pos << endl;
            }
            node = node->next;
        }
    }
    void display()
    {
        Node *temp = head;
        if (!temp)
        {
            cout << "List is empty!!\n";
            return;
        }
        int len = 0;
        while (temp)
        {
            len++;
            cout << "ID:" << temp->ID << ", Name:" << temp->name << ", Severity:" << temp->severity << ", Arrival:" << temp->Arrival << "AM" << endl;
            temp = temp->next;
        }
        cout << "There are total " << len << " patients\n";
    }

    void addNode(int s, string n, int id, string a)
    {
        Node *node = new Node();
        Node *temp;
        temp = head;
        node->Arrival = a;
        node->ID = id;
        node->name = n;
        node->severity = s;

        if (node->severity == 5)
        {
            insertAtFront(s, n, id, a);
        }
        else if (node->severity == 1)
        {
            insertAtEnd(s, n, id, a);
        }
    }

    void insertAtPos(int pos, int s, string n, int id, string a)
    {
        Node *node = new Node();
        node->Arrival = a;
        node->ID = id;
        node->name = n;
        node->severity = s;

        Node *temp;
        temp = head;
        if (pos < 1)
        {
            cout << "Invalid index!!!\n";
            return;
        }

        if (pos == 1)
        {
            insertAtFront(s, n, id, a);
            return;
        }

        for (int i = 0; i < pos - 1 && temp; i++)
        {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    void removeFromStart()
    {
        if (!head)
        {
            cout << "List is empty!!\n";
            return;
        }

        Node *temp = head;
        head = head->next;
        delete temp;
    }

    void removePatient(int id)
    {
        if (!head)
        {
            cout << "List is empty!!\n";
            return;
        }

        if (head->ID == id)
        {
            removeFromStart();
            return;
        }

        Node *temp = head;
        Node *prev = NULL;

        while (temp && temp->ID != id)
        {
            prev = temp;
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "Patient not found!\n";
            return;
        }
        prev->next = temp->next;
        delete temp;
    }

    void removeFromLast()
    {
        if (!head)
        {
            cout << "List is empty!!\n";
            return;
        }
        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
       temp = NULL;
       delete temp;
    }
};

int main()
{

    Patient list;
    list.addNode(1, "Charlie", 103, "10:10");
    list.addNode(5, "Dave", 104, "10:15");
    list.insertAtPos(2, 4, "Eve", 105, "10:20");
    list.searching(103);
    list.removeFromStart();
    list.removePatient(105);
    list.removePatient(103);
    list.removeFromLast();
    list.display();
    return 0;
}