#include <iostream>
using namespace std;

struct Node
{
    int phoneNo;
    string customerID;
    Node *next;
    Node(string id, int no)
    {
        phoneNo = no;
        customerID = id;
        next = NULL;
    }
};

class CircularCallQueue
{
private:
    Node *head;

public:
    CircularCallQueue()
    {
        head = NULL;
    }

    void insertAtStart(int n, string id)
    {
        Node *node = new Node(id, n);
        if (!head)
        {
            head = node;
            head->next = head;
            return;
        }
        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->next = head;
        head = node;
    }

    void insertAtEnd(int n, string id)
    {
        Node *node = new Node(id, n);
        if (!head)
        {
            head = node;
            head->next = head;
            return;
        }
        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->next = head;
    }

    void insertAtPos(int pos, int n, string id)
    {
        Node *node = new Node(id, n);
        if (!head)
        {
            head = node;
            head->next = head;
            return;
        }

        if (pos == 1)
        {
            insertAtStart(n, id);
            return;
        }

        Node *temp = head;
        int current = 1;
        while (current < pos - 1 && temp->next != head)
        {
            temp = temp->next;
            current++;
        }

        node->next = temp->next;
        temp->next = node;
    }

    void deleteAtStart()
    {
        if (!head)
        {
            cout << "No active calls!\n";
            return;
        }
        Node *temp = head;
        if (head->next == head)
        {
            delete head;
            head = NULL;
            return;
        }

        Node *last = head;
        while (last->next != head)
        {
            last = last->next;
        }
        head = head->next;
        last->next = head;
        delete temp;
    }

    void deleteAtEnd()
    {
        if (!head)
        {
            cout << "No active calls!\n";
            return;
        }
        Node *temp = head, *prev = NULL;
        if (head->next == head)
        {
            delete head;
            head = NULL;
            return;
        }

        while (temp->next != head)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = head;
        delete temp;
    }

    void deleteAtPos(int pos)
    {
        if (!head)
        {
            cout << "No active calls!\n";
            return;
        }

        if (pos == 1)
        {
            deleteAtStart();
            return;
        }

        Node *temp = head, *prev = NULL;
        int current = 1;
        while (current < pos && temp->next != head)
        {
            prev = temp;
            temp = temp->next;
            current++;
        }

        if (current == pos)
        {
            prev->next = temp->next;
            delete temp;
        }
    }

    bool searchCall(string id, int no)
    {
        if (!head)
        {
            return false;
        }

        Node *temp = head;
        do
        {
            if (temp->customerID == id || temp->phoneNo == no)
            {
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    int countCalls()
    {
        if (!head)
        {
            return 0;
        }

        Node *temp = head;
        int count = 1;

        while (temp->next != head)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

    void display()
    {
        if (!head)
        {
            cout << "No active calls!\n";
            return;
        }

        Node *temp = head;
        do
        {
            cout << temp->customerID << "," << temp->phoneNo << " -> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(Head)\n";
    }
};

int main()
{
    CircularCallQueue callQueue;

    callQueue.insertAtEnd(300, "23i-3101");
    callQueue.insertAtEnd(320, "23i-3010");
    callQueue.insertAtStart(325, "VIP-3052");
    callQueue.insertAtPos(2, 399, "VIP-3042");
    cout << "Call Queue:\n";
    callQueue.display();
    callQueue.deleteAtStart();
    cout << "\nAfter completing the first call:\n";
    callQueue.display();
    callQueue.deleteAtPos(2);
    cout << "\nAfter removing a call at position 2:\n";
    callQueue.display();
    string searchID = "23i-3010";
    int searchPhone = 320;
    if (callQueue.searchCall(searchID, searchPhone))
    {
        cout << "\nCall from " << searchID << " is still in the queue.\n";
    }
    else
    {
        cout << "\nCall from " << searchID << " is not in the queue.\n";
    }
    cout << "\nTotal Active Calls: " << callQueue.countCalls() << endl;

    return 0;
}
