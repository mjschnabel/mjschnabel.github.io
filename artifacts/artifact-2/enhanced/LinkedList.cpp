//============================================================================
// Name        : LinkedList.cpp
// Author      : Mark Schnabel
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    int size = 0;

    // Creates a new struct to represent a single node in the linked list.
    // Each node contains a bid and a pointer to the next node in the list.
    struct Node {
        Bid bid;
        Node* next;

        // Default constructor.
        // Initializes the struct with a nullptr to the next node
        Node() {
            next = nullptr;
        }

	    // Constructor for creating a node with a Bid
        Node(Bid newBid) {
            bid = newBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    void InsertionSort();
    bool Insert(Bid newBid, string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // Ensure the list will have a head and tail node upon initialization.
    // These are critical variables for finding the start and end of the list.
    // Default value for these variables is nullptr since the list should start out empty
	head = nullptr;
	tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // Start by creating a new node with the big to add to the list
    Node* newNode = new Node(bid);

    // If the list is empty (head is null), then set the new node to be the head
    // of the list as it is the only node in the list
	if (head == nullptr) {
		head = newNode;
	} else {
        // Else if the list is not empty, then set the next pointer on the tail
        // to point to the new node as long as the tail is not null
        if (tail != nullptr) {
            tail->next = newNode;
        }
	}

    // Ensure that the new node is now the new tail since it is now the last item in the list
    tail = newNode;

    // Increment the size of the list since a new node was just added
	size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // Start by creating a new node with the bid
	Node* newNode = new Node(bid);

	// If the list is empty (head is null), then immediately set the new node to be the head
    // of the list
	if (head == nullptr) {
		head = newNode;
	} else {
        // If the list is not empty, then set the next pointer on the new node to point to
        // the current head, and then set the head to be the new node since it is now the
        // first item in the list
		newNode->next = head;
		head = newNode;
	}

    // Increment the size of the list since a new node was just added
	size++;
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // Start by instantiating a new node to hold the current node. Make the current node start
    // as the head since that is the first node in the list.
	Node* currentNode = head;

    // Loop until it hits the end of the list (i.e. when the next node is null)
	while (currentNode != nullptr) {
        // Print out all the data for the bid
        cout << currentNode->bid.bidId << ": " << currentNode->bid.title << " | " << currentNode->bid.amount
            << " | " << currentNode->bid.fund << endl;

        // Set the current node to be the next node in the list
        // so that node can now be printed out.
		currentNode = currentNode->next;
	}

}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // Initialize two variables, one called currentNode to track what the current node in the list we are looking at is
    // and one called nextNode, to track what the next node in the list that we will look at is.
    // By default, currentNode should start as the head node of the list so that we can track it.
	Node* currentNode = head;
	Node* nextNode = currentNode->next;

    // First do a check to see if the current node is the one we are looking to delete.
    // If it is that means it's the head node that we are trying to remove and we need to replace it.
	if (currentNode->bid.bidId == bidId) {
		delete currentNode;
		head = nextNode;

        // Once deleted decrement the size of the list and return
		size--;
		return;
	}

    // If it was not the head of the list that we were looking to delete, enter into a loop
    // And continously check to see if the next node is the bid we want to delete.
	while (currentNode != nullptr) {
		if (nextNode->bid.bidId == bidId) {
            // If we did find the node we want to delete,
            // then assign the next node of the nextNode to be the next node of the currentNode and delete the nextNode
			Node* tmpNode = nextNode->next;
			currentNode->next = tmpNode;
			delete nextNode;

            // Once deleted decrement the size of the list and return
			size--;
			return;
		} else {
            // If we did not find the node we want to delete, jump to the next set of nodes
            currentNode = currentNode->next;
            nextNode = currentNode->next;
        }
	}
}

/**
 * Performs an insertion sort algorithm on the list of bids
 */
void LinkedList::InsertionSort() {
    // Initialize two variables, one to hold a pointer to the head of the new sorted linked list
    // and another to hold the current node that were are iterating over
    Node* sortedListHead = NULL;
    Node* currentNode = head;

    // Start a loop and continue it until there are no more elements left in the original list
    while (currentNode != nullptr) {
        // Get the next node that we will need to iterate over
        Node* nextNode = currentNode->next;

        // If the sorted list head is NULL or the sorted list head is greater than the current node
        // insert the current node before the sorted list head
        if (sortedListHead == NULL || sortedListHead->bid.title.compare(currentNode->bid.title) >= 0) {
            currentNode->next = sortedListHead;
            sortedListHead = currentNode;
        } else {
            // Create a new node to hold the place we are at in the sorted list
            // and initialize it to the sorted list head
            Node *sortedCurrentNode = sortedListHead;

            // Loop through all the nodes in the sorted list until we've found a node that node that is lesser
            // than the old current node or we've hit the end of the list
            while (sortedCurrentNode->next != NULL && sortedCurrentNode->next->bid.title.compare(currentNode->bid.title) < 0) {
                sortedCurrentNode = sortedCurrentNode->next;
            }

            // Put the sortedCurrentNode behind the currentNode
            currentNode->next = sortedCurrentNode->next;
            sortedCurrentNode->next = currentNode;
        }

        currentNode = nextNode;
    }

    // Re-assign head to point at the head of the sorted list
    head = sortedListHead;
}

/**
 * Inserts a bid into the list after a bid with a given bid ID.
 * Returns true if inserted successfully
 * Returns false if the bid to insert the new bid in after was not found.
 *
 * @param bid The new bid to insert into the list
 * @param bidId The bid id of the bid you want the new bid to be inserted after
 */
bool LinkedList::Insert(Bid newBid, string bidId) {
	Node* currentNode = head;

	while (currentNode != nullptr) {
        // If the current node contains the bid we are looking for
        // insert the new bid after it
		if (currentNode->bid.bidId == bidId) {
            Node newBidNode = Node(newBid);
			Node* tmpNode = currentNode->next;
            currentNode->next = &newBidNode;
            newBidNode.next = tmpNode;
			return true;
		}

        // Else jump to the next node in the list
		currentNode = currentNode->next;
	}

    return false;
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // Start by initializing two variables, a node to use to iterate over the list until we find the correct variable
    // and an empty bid to hold the bid we are searching for
	Node* currentNode = head;
	Bid bid;

	while (currentNode != nullptr) {
        // If the current node contains the bid we are looking for return the bid
		if (currentNode->bid.bidId == bidId) {
			return currentNode->bid;
		}

        // Else jump to the next node in the list
		currentNode = currentNode->next;
	}

    // Return the empty bid if no bid is found
	return bid;
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
		cout << "  6. Prepend Bid" << endl;
		cout << "  7. Insert Bid" << endl;
		cout << "  8. Insertion Sort" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            cout << "Enter the ID of the Bid you would like to delete: ";

            cin >> bidKey;
            bidList.Remove(bidKey);

            break;

        case 6:
            bid = getBid();
            bidList.Prepend(bid);
            displayBid(bid);

            break;

        case 7:
            bid = getBid();
            bidList.Insert(bid, bidKey);
            bidList.PrintList();

            break;

        case 8:
            bidList.InsertionSort();
            bidList.PrintList();

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
