#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node
{
    string name;
    long long int phone_number;
    Node *next;
    Node *prev;
};

class ContactBook
{
    Node *head;

public:
    ContactBook()
    {
        head = NULL;
    }

    void createNode()
    {
        Node *newer = new Node;
        cout << "Name of Contact:";
        cin >> newer->name;

        cout << "Phone Number:";
        string phoneNumberStr;
        cin >> phoneNumberStr;

        // Validate if the input contains only digits
        if (phoneNumberStr.find_first_not_of("0123456789") != string::npos)
        {
            cout << "Invalid phone number. Please enter a valid integer phone number." << endl;
            return;
        }

        // Convert the validated input to a long long integer
        stringstream ss(phoneNumberStr);
        long long int phoneNumber;
        ss >> phoneNumber;
        newer->phone_number = phoneNumber;

        newer->next = NULL;
        newer->prev = NULL;

        if (head == NULL)
        {
            head = newer;
        }
        else
        {
            Node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newer;
            newer->prev = temp;
        }

        cout << "Contact Added successfully" << endl;
    }

    void display()
    {
        Node *temp = head;
        int count = 0;

        if (temp == NULL)
        {
            cout << "No Contacts.... Please Add some Contacts " << endl;
            cout << "Thanks" << endl;
        }
        else
        {
            cout << "Name\tNumber" << endl;
            while (temp != NULL)
            {
                count++;
                cout << temp->name << "\t" << temp->phone_number << endl;
                temp = temp->next;
            }
            cout << "Total Contacts:" << count << endl;
        }
    }

    void bubbleSort()
    {
        Node *i, *j;
        string n;
        long long int n2;

        for (i = head; i->next != NULL; i = i->next)
        {
            for (j = i->next; j != NULL; j = j->next)
            {
                if (i->name > j->name)
                {
                    n = i->name;
                    i->name = j->name;
                    j->name = n;

                    n2 = i->phone_number;
                    i->phone_number = j->phone_number;
                    j->phone_number = n2;
                }
            }
        }
    }

    void deleteContact()
    {
        string deleteName;
        cout << "Enter the name to delete: ";
        cin >> deleteName;

        Node *temp = head;
        Node *prev = NULL;
        bool found = false;
        while (temp != NULL)
        {
            if (temp->name == deleteName)
            {
                found = true;
                if (prev == NULL) // Deleting the head node
                {
                    head = temp->next;
                    if (head != NULL)
                    {
                        head->prev = NULL;
                    }
                }
                else
                {
                    prev->next = temp->next;
                    if (temp->next != NULL)
                    {
                        temp->next->prev = prev;
                    }
                }
                delete temp;
                cout << "Contact deleted successfully." << endl;
                break;
            }
            prev = temp;
            temp = temp->next;
        }

        if (!found)
        {
            cout << "Contact not found." << endl;
        }
    }
    void updateContact()
    {
        string updateName;
        cout << "Enter the name to update: ";
        cin >> updateName;

        Node *temp = head;
        bool found = false;
        while (temp != NULL)
        {
            if (temp->name == updateName)
            {
                found = true;
                cout << "Contact found. Enter new details:" << endl;
                cout << "New Name: ";
                cin >> temp->name;

                string phoneNumberStr;
                cout << "New Phone Number:";
                cin >> phoneNumberStr;

                // Validate if the input contains only digits
                if (phoneNumberStr.find_first_not_of("0123456789") != string::npos)
                {
                    cout << "Invalid phone number. Please enter a valid integer phone number." << endl;
                    return;
                }

                // Convert the validated input to a long long integer
                stringstream ss(phoneNumberStr);
                long long int phoneNumber;
                ss >> phoneNumber;
                temp->phone_number = phoneNumber;

                cout << "Contact updated successfully." << endl;
                break;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "Contact not found." << endl;
        }
    }

    void saveToFile()
    {
        ofstream myfile("contactbook.txt");
        Node *temp = head;

        if (myfile.is_open())
        {
            while (temp != NULL)
            {
                myfile << temp->name << endl;
                myfile << temp->phone_number << endl;
                temp = temp->next;
            }
            myfile.close();
        }
        else
        {
            cout << "Unable to open file";
        }
    }

    void readFromFile()
    {
        ifstream myfile("contactbook.txt");
        if (myfile.is_open())
        {
            string name;
            long long int phone_number;

            while (myfile >> name >> phone_number)
            {
                Node *newer = new Node;
                newer->name = name;
                newer->phone_number = phone_number;
                newer->next = NULL;

                if (head == NULL)
                {
                    head = newer;
                }
                else
                {
                    Node *temp = head;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = newer;
                    newer->prev = temp;
                }
            }
            myfile.close();
        }
        else
        {
            cout << "Unable to open file";
        }
    }
    void findContact()
    {
        string searchName;
        cout << "Enter the name to search for: ";
        cin >> searchName;

        Node *temp = head;
        bool found = false;
        while (temp != NULL)
        {
            if (temp->name == searchName)
            {
                found = true;
                cout << "Contact found:" << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Phone Number: " << temp->phone_number << endl;
                break;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "Contact not found." << endl;
        }
    }

    void menu()
    {
        while (true)
        {
            cout << "******************" << endl;
            cout << "1. Add contact" << endl;
            cout << "2. Display contacts" << endl;
            cout << "3. Delete contacts" << endl;
            cout << "4. Update contacts" << endl;
            cout << "5. Save contacts to file" << endl;
            cout << "6. Load contacts from file" << endl;
            cout << "7. Find Contacts" << endl;
            cout << "8. Exit" << endl;

            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                createNode();
                break;
            case 2:
                display();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                readFromFile();
                break;
            case 7:
                findContact();
                break;

            case 8:
                saveToFile();
                cout << "Exiting program..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main()
{
    ContactBook cb;
    cb.readFromFile();

    cout << "WELCOME TO CONTACTBOOK" << endl;
    cb.menu();

    return 0;
}
