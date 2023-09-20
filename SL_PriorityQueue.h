/** ADT priority queue: ADT sorted list implementation.
 Listing 14-6.
 @file SL_PriorityQueue.h */

#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_

#include <memory>
#include "PriorityQueueInterface.h"
#include "LinkedSortedList.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class SL_PriorityQueue : public PriorityQueueInterface<ItemType>
{
private:
   std::unique_ptr<LinkedSortedList<ItemType>> slistPtr;  // Pointer to sorted list of
                                          // items in the priority queue

public:
   SL_PriorityQueue();
   SL_PriorityQueue(const SL_PriorityQueue& pq);
   ~SL_PriorityQueue();

   bool isEmpty() const;
   bool enqueue(const ItemType& newEntry);
   bool dequeue();

   /** @throw PrecondViolatedExcep if priority queue is empty. */
   ItemType peek() const throw(PrecondViolatedExcep);
}; // end SL_PriorityQueue

#include "SL_PriorityQueue.cpp"
#endif
