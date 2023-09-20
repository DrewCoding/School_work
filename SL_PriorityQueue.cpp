/** ADT priority queue: ADT sorted list implementation.
 @file SL_PriorityQueue.cpp */
 
#include "SL_PriorityQueue.h"  // Header file

template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue()
   : slistPtr(std::make_unique<LinkedSortedList<ItemType>>())

{     }  // end default constructor

template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue(const SL_PriorityQueue& pq)
   : slistPtr(std::make_unique<LinkedSortedList<ItemType>>())
{
	// Add items to it using public methods
	for (int position = 1; position <= pq.slistPtr->getLength(); position++)
	{
		slistPtr->insertSorted(pq.slistPtr->getEntry(position));
	}  // end for
}  // end copy constructor

template<class ItemType>
SL_PriorityQueue<ItemType>::~SL_PriorityQueue()
{
}  // end destructor

template<class ItemType>
bool SL_PriorityQueue<ItemType>::isEmpty() const
{
   return slistPtr->isEmpty();
}  // end isEmpty

template<class ItemType>
bool SL_PriorityQueue<ItemType>::enqueue(const ItemType& newEntry)
{ 
   slistPtr->insertSorted(newEntry);
   return true;
}  // end add

template<class ItemType>
bool SL_PriorityQueue<ItemType>::dequeue()
{
   // The highest priority item is at the end of the sorted list
   return slistPtr->remove(slistPtr->getLength());
}  // end remove
   
template<class ItemType>
ItemType SL_PriorityQueue<ItemType>::peek() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("peekFront() called with empty queue.");
   
   // Priority queue is not empty; return highest priority item;
   // it is at the end of the sorted list
   return slistPtr->getEntry(slistPtr->getLength());
}  // end peek


