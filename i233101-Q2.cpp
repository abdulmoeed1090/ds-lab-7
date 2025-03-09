#include <iostream>
using namespace std;

struct Node
{
    int seatNo;
    string name;
    Node *prev;
    Node *next;

    Node(int no, string n)
    {
        seatNo = no;
        name = n;
        prev = NULL;
        next = NULL;
    }
};

class TicketBookingSystem
{
private:
    Node *head;
    Node *tail;

public:
    TicketBookingSystem()
    {
        head = NULL;
        tail = NULL;
    }

    void insertAtStart(int no, string n)
    {
        Node *node = new Node(no, n);
        if (!head)
        {
            head = tail = node;
            return;
        }
        node->next = head;
        head->prev = node;
        head = node;
    }

    void insertAtEnd(int no, string n)
    {
        Node *node = new Node(no, n);
        if (!head)
        {
            head = tail = node;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    void insertAtPos(int pos, int no, string n)
    {
        if (pos <= 1)
        {
            insertAtStart(no, n);
            return;
        }

        Node *temp = head;
        int count = 1;

        while (temp && count < pos - 1)
        {
            temp = temp->next;
            count++;
        }

        if (!temp)
        {
            insertAtEnd(no, n);
            return;
        }

        Node *node = new Node(no, n);
        node->next = temp->next;
        node->prev = temp;

        if (temp->next)
        {
            temp->next->prev = node;
            temp->next = node;
        }
        if (!node->next)
        {
            tail = node;
        }
    }

    void deleteAtStart()
    {
        if (!head)
        {
            cout << "No bookings available \n";
            return;
        }
        Node *temp = head;
        head = head->next;

        if (head)
        {
            head->prev = NULL;
        }
        else
        {
            tail = NULL;
        }
        delete temp;
        cout << "Earliest booking canceled\n";
    }

    void deleteAtEnd()
    {
        if (!head)
        {
            cout << "No bookings available \n";
            return;
        }
        Node *temp = tail;
        tail = tail->prev;

        if (tail)
        {
            tail->next = NULL;
        }
        else
        {
            head = NULL;
        }
        delete temp;
        cout << "Last booking canceled.\n";
    }

    void deleteAtPos(int pos)
    {
        if (!head)
        {
            cout << "No bookings available \n";
            return;
        }

        if (pos == 1)
        {
            deleteAtStart();
            return;
        }

        Node *temp = head;
        int count = 1;

        while (temp && count < pos)
        {
            temp = temp->next;
            count++;
        }

        if (!temp)
        {
            cout << "Invalid position!\n";
            return;
        }

        if (temp == tail)
        {
            deleteAtEnd();
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;

        cout << "Booking at position " << pos << " is deleted\n";
    }

    void searchBySeatNo(int no)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->seatNo == no)
            {
                cout << "Booking found: Seat " << temp->seatNo << " is booked by " << temp->name << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Seat number " << no << " not found\n";
    }

    void searchByName(string n)
    {
        Node *temp = head;
        bool found = false;

        while (temp)
        {
            if (temp->name == n)
            {
                cout << "Booking found: " << temp->name << " has booked Seat " << temp->seatNo << "\n";
                found = true;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "No booking found for customer: " << n << "\n";
        }
    }

    void display()
    {
        if (!head)
        {
            cout << "List is empty!!\n";
            return;
        }

        Node *temp = head;
        cout << "Forward direction:\n";
        while (temp)
        {
            cout << temp->seatNo << ", " << temp->name << " <-----> ";
            temp = temp->next;
        }
        cout << "NULL\n";

        cout << "Reverse direction:\n";
        temp = tail;
        while (temp)
        {
            cout << temp->seatNo << ", " << temp->name << " <-----> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }

    void lengthCalculation()
    {
        Node *temp = head;
        int len = 0;
        while (temp)
        {
            len++;
            temp = temp->next;
        }
        cout << "Length of doubly linked list = " << len << endl;
    }
};

int main()
{
    TicketBookingSystem list;

    list.insertAtStart(5, "Yasim");
    list.insertAtEnd(10, "Ali");
    list.insertAtPos(2, 7, "Sammad");

    list.display();
    list.lengthCalculation();

    cout << "\nDeleting first booking...\n";
    list.deleteAtStart();
    list.display();

    cout << "\nDeleting last booking...\n";
    list.deleteAtEnd();
    list.display();

    cout << "\nDeleting booking at position 2...\n";
    list.deleteAtPos(2);
    list.display();

    cout << "\nSearching for Seat 7...\n";
    list.searchBySeatNo(7);

    cout << "\nSearching for customer Ali...\n";
    list.searchByName("Ali");

    return 0;
}
