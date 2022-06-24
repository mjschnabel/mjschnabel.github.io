# Artifact 2 - Algorithms and Data Structures

For this milestone, the artifact I’ve chosen to enhance is the code from the final project of the class CS-260 Algorithms and Data Structures. This project was completed about halfway through my degree program here at SNHU. The original project tasked us students with creating a variety of Data Structures and Algorithms in C++. We learned about these Algorithms and Data Structures through the entire course and for the final project we had to write a paper describing these Algorithms and data structures and their use case. One of the data structures that we went over in the course was the Linked List. A Linked List is basically a list of elements that is linked together because each element contains a reference to the next element in the list. For my enhancement, I chose to extend the base LinkedList class I created in the course to have more functionality and utilize a new algorithm that the original did not have. I believe that this will demonstrate my proficiency in Data Structures because it shows I can work with Data Structures and build functionality around them, and it also shows I have an understanding of how to work with common Algorithms and can implement them in a real use case.

I did two things for this enhancement. The first was I implemented an “Insert” function into the base LinkedList class. Previously the class had methods for prepending and appending elements to the list which was nice, however when using this class in a real world scenario there may be occasions where you would need to be able to add data into the list not just at the beginning of the list or at the end of the list, but somewhere in the middle of it. The way I implemented this was I created a function that would take two parameters, a bid object and a bidId string. For some context, the original project had us create data structures and algorithms to interact with a CSV file containing “bids” from an auction house, so naturally the data structures we created in the class stored “bid” objects to represent these bids and the algorithms performed operations on these bids. My function would then iterate through all the bids in the list until it found a bid with an ID that matched the bidId parameter and it would insert the new bid that was passed as a parameter into the list after that bid. That was what the bidId parameter was for, it allowed you to specify which bid you wanted to insert the item after. In the case that no matching bid ID was found, the function would return false to let the caller know that the insert operation was unsuccessful. It would also do the opposite when a bid with a matching ID was found and the insertion was successful and it would return true. The full code for the function can be seen below:
  
```
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
```

I believe that this change showed my proficiency in the realm of data structures because it showed that I can work with an existing data structure and understand its components well enough to extend its functionality and be more useful overall.

The next improvement I made to the original artifact was I again extended the class by adding a function that would call a well known algorithm on the data in the list called Insertion Sort. Insertion Sort is a sorting algorithm that works by splitting an array into a sorted and unsorted section. It gets its name “Insertion Sort” because the way it handles the sorting is by taking elements from the unsorted part of the list and inserting them into the correct position in the sorted part. (Insertion Sort. Brilliant.org. Retrieved 22:42, June 23, 2022, from https://brilliant.org/wiki/insertion/). 
Insertion Sort is not necessarily the most efficient algorithm. It has a best case time complexity of O(n) meaning that at a minimum it will need to iterate over each and every element in the list. It has a worst case complexity of O(n^2) meaning that it can take a proportional amount of time to sort the list to the square of the number of elements in the list. The worst case occurs when all the elements are in reverse sorted order and the inner loop of the algorithm needs to run n*n times. (Alake, R, Insertion sort explained–a data scientists algorithm guide 2021)
The algorithm definitely works best with smaller or nearly sorted lists. However, despite insertion sort not always being the most efficient sorting algorithm, it is preferred for a data structure like a linked list because linked lists provide pointers to the next element which is very useful for keeping track of the previous and next elements in the list which you need to do when implementing insertion sort. Other algorithms such as Quick Sort and Heap Sort perform horribly or are impossible on a linked list due to the fact that linked lists provide very slow random access to elements which is necessary for those sorting algorithms to work. (OpenGenus Foundation, Insertion sort a linked list 2018) 

I chose this algorithm as it kept with the theme I had already been running with when I added my Insert function, but also because I believe there is real utility in having a sorting function easily available for a data structure such as this. The way my implementation worked was it initialized a new list for the sorted elements, iterated over each element in the unsorted list by jumping from reference to reference and along the way doing comparisons to find where each element would belong in the new list. Once all the elements had been iterated over, the sorted list would be set as the main list value for the class. My algorithm implementation specifically sorted the elements by the title of their bid. I thought this would be the most useful property to sort off, but this could be extended in the future to sort based off of any property in the bid object.. I believe implementing this algorithm demonstrated my capabilities in the category of Algorithms as it showed I can implement a classic algorithm on top of a custom implementation of a data structure. The code for the algorithm can be seen below:

```
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
```

I believe that I did meet the objectives I set out for myself when deciding upon enhancing this artifact. I set out to extend the functionality of the data structure and implement a common algorithm on the data structure and I believe that I did that. I did not know exactly how I was going to extend the data structure or what algorithm I would choose to implement. I came to that decision when I went to do the actual implementation. 

while making this enhancement, I did not learn anything necessarily new. I had previously researched data structures and algorithms thoroughly, through my courses and my own personal interest. However, this was a nice refresher into the subject of data structures and algorithms and allowed me to get back into an algorithmic mindset and dive back into the topic of time complexity, which is easy to forget all the details of as it is such a abstract topic and you do not need to interact with it every day.

## References
Insertion sort. Brilliant Math & Science Wiki. (n.d.). Retrieved June 23, 2022, from https://brilliant.org/wiki/insertion/#insertion-sort 
Alake, R. (2021, December 16). Insertion sort explained–a data scientists algorithm guide. NVIDIA Technical Blog. Retrieved June 23, 2022, from https://developer.nvidia.com/blog/insertion-sort-explained-a-data-scientists-algorithm-guide/#:~:text=The%20best%2Dcase%20time%20complexity,already%20in%20the%20correct%20order. 
Foundation, O. G. (2018, August 14). Insertion sort a linked list. OpenGenus IQ: Computing Expertise & Legacy. Retrieved June 23, 2022, from https://iq.opengenus.org/insertion-sort-linked-list/#:~:text=Insertion%20Sort%20is%20preferred%20for,as%20Heap%20Sort%20completely%20impossible. 
