#include <iostream>
#include <queue>
#include <string>
#include <iomanip>   // for setw() and setfill()
#include <algorithm> // for all_of()

using namespace std;

// class representing a person with a name and ticket number
class Person {
public:
    string name;
    int ticketNum;

    // constructor to initialize a person with a name and ticket number
    Person(string n, int t) : name(n), ticketNum(t) {}
};

// class representing a queue system for managing people and their tickets
class Queue {
private:
    queue<Person> line;  // standard queue to hold person objects
    int next_ticket_number = 1;  // counter to generate sequential ticket numbers

public:
    // function to add a person to the queue
    void enqueue(const string& name) {
        if (name.empty()) {  // check for empty input
            cout << "Name cannot be empty. Please try again." << endl;
            return;
        }
        // create a new person with the next available ticket number
        Person newPerson(name, next_ticket_number++);
        line.push(newPerson);  // add the person to the queue

        cout << name << " added to the queue with ticket #" << setw(3) << setfill('0') << newPerson.ticketNum << endl;
        cout << "Queue size: " << size() << endl;
    }

    // function to remove (serve) the person at the front of the queue
    void dequeue() {
        if (!is_empty()) {  // check if the queue is not empty
            Person next = line.front();  // get the person at the front
            line.pop();  // remove them from the queue

            cout << "\nAfter 1 minute..." << endl;
            cout << "Dequeue: " << next.name << " served (Ticket #" << setw(3) << setfill('0') << next.ticketNum << ")" << endl;
            cout << "Queue size: " << size() << endl;
            peek();  // display the next person in line
        } else {
            cout << "\nThe queue is empty. no one to serve." << endl;
        }
    }

    // function to show the person currently at the front of the queue
    void peek() const {
        if (!is_empty()) {  // check if the queue is not empty
            Person next = line.front();  // get the front person
            cout << "Next in line: " << next.name << " (Ticket # " << setw(3) << setfill('0') << next.ticketNum << ")" << endl;
        } else {
            cout << "Queue is empty." << endl;
        }
    }

    // check if the queue is empty
    bool is_empty() const {
        return line.empty();
    }

    // return the current size of the queue
    size_t size() const {
        return line.size();
    }

    // function to check a person's position by name or ticket number
    void position(const string& input) const {
        queue<Person> temp = line;  // create a copy of the queue
        int pos = 1;  // position counter
        bool found = false;  // flag to check if person is found

        bool is_ticket_number = all_of(input.begin(), input.end(), ::isdigit);  // check if input is a number

        while (!temp.empty()) {  // iterate through the queue to find the person
            Person p = temp.front();  // get the front person
            temp.pop();  // remove the front person from the temp queue

            if ((is_ticket_number && to_string(p.ticketNum) == input) || 
                (!is_ticket_number && p.name == input)) {  // compare by name or ticket number
                cout << p.name << " is currently at position " << pos << " in the queue." << endl;
                found = true;
                break;
            }
            pos++;
        }
        if (!found) {
            cout << input << " is not in the queue." << endl;
        }
    }
};

int main() {
    Queue q;  // create a queue instance
    int choice;
    string input;

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << endl;

    do {
        cout << "\n1. Enqueue a person\n";
        cout << "2. Check your position in the queue\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();  // clear newline left in the buffer

        switch (choice) {
            case 1:
                cout << "Enter the name: ";
                getline(cin, input);  // use getline to capture full names
                q.enqueue(input);  // add the person to the queue
                break;
            case 2:
                cout << "Enter your name or ticket number: ";
                getline(cin, input);  // capture input with spaces or numbers
                q.position(input);  // check the person's position
                break;
            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (q.size() > 0 && q.size() % 3 == 0) {  // automatically serve the next person every 3 enqueues
            cout << "Automatically processing the next person in line..." << endl;
            q.dequeue();
        }

    } while (choice != 3);  // repeat until the user chooses to exit

    return 0;
}
