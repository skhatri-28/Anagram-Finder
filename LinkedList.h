/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// This struct represents an individual node within a linked list.  A node
// contains next and prev pointers. The node uses a void pointer and can
// hold any type of data.
typedef struct ll_node {
  void *data;
  struct ll_node *next;  // next node in list, or NULL
  struct ll_node *prev;  // prev node in list, or NULL
} LinkedListNode, *LinkedListNodePtr;

// This struct represents the entire linked list.  We provided a struct
// declaration (but not definition) in LinkedList.h; this is the associated
// definition.  This struct contains metadata about the linked list.
typedef struct ll_head {
  int num_elements;   //  # elements in the list
  LinkedListNodePtr head;  // head of linked list, or NULL if empty
  LinkedListNodePtr tail;  // tail of linked list, or NULL if empty
} LinkedListHead;

// A LinkedList is a pointer to a ll_head struct.
// To hide the implementation of LinkedList, we declare the "struct ll_head"
// structure here.
typedef struct ll_head *LinkedList;

// Creates a LinkedListNode by malloc'ing the space.
//
// INPUT: A void pointer to the data the LinkedListNode will hold. A void
// pointer
// is used so the linkedlist can store any type of data.
//
// Returns a pointer to the new LinkedListNode.
LinkedListNode *CreateLinkedListNode(void *data);

// Destroys and free's a provided LLNode.
//
// INPUT: A pointer to the node to destroy.
//
// Returns 0 if the destroy was successful, -1 otherwise.
int DestroyLinkedListNode(LinkedListNodePtr node);

// Creates a LinkedList.
// The customer is responsible for calling DestroyLinkedList()
// to destroy and free the LinkedList when done.
//
// Returns a LinkedList; NULL if there's an error.
LinkedList CreateLinkedList();

// Destroys a LinkedList.
// All structs associated with a LinkedList will be
// released and freed.
//
// INPUT: A pointer to a LinkedList.
//
void DestroyLinkedList(LinkedList list);

// Adds an element to the head of a LinkedList
//
// INPUT: A pointer to the LinkedList that will be added to.
// INPUT: A void pointer for the data to be added to the head of the linkedlist
//
// Returns 0 if the insertion was successful; non-zero for failure.
int InsertLinkedList(LinkedList, void *data);

// Gets the number of elements in the LinkedList
//
// INPUT: A linkedlist whose number of elements you want to obtain
//
// Returns the number of elements in the linkedlist
int NumElemsInLinkedList(LinkedList list);

#endif  // LINKEDLIST_H
