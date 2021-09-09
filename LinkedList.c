/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdio.h>
#include "LinkedList.h"

// Creates a LinkedListNode by malloc'ing the space.
//
// INPUT: A void pointer to the data the LinkedListNode will hold. A void
// pointer
// is used so the linkedlist can store any type of data.
//
// Returns a pointer to the new LinkedListNode.
LinkedListNode* CreateLinkedListNode(void* data) {
  LinkedListNodePtr node = (LinkedListNodePtr)malloc(sizeof(LinkedListNode));
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

// Destroys and free's a provided LLNode.
//
// INPUT: A pointer to the node to destroy.
//
// Returns 0 if the destroy was successful, -1 otherwise.
int DestroyLinkedListNode(LinkedListNodePtr node) {
  if (node == NULL) {
    return -1;
  } else {
    free(node->data);
    free(node);
    return 0;
  }
}

// Creates a LinkedList.
// The customer is responsible for calling DestroyLinkedList()
// to destroy and free the LinkedList when done.
//
// Returns a LinkedList; NULL if there's an error.
LinkedList CreateLinkedList() {
  LinkedList linked_list = (LinkedList)malloc(sizeof(struct ll_head));
  if (linked_list != NULL) {
    linked_list->num_elements = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;
    return linked_list;
  } else {
    return NULL;
  }
}

// Destroys a LinkedList.
// All structs associated with a LinkedList will be
// released and freed.
//
// INPUT: A pointer to a LinkedList.
//
void DestroyLinkedList(LinkedList list) {
  LinkedListNodePtr cur_node = list->head;
  LinkedListNodePtr next_node = cur_node->next;
  while (cur_node != NULL) {
    DestroyLinkedListNode(cur_node);
    cur_node = next_node;
    if (cur_node != NULL) {
      next_node = cur_node->next;
    }
  }
  free(list);
}

// Adds an element to the head of a LinkedList
//
// INPUT: A pointer to the LinkedList that will be added to.
// INPUT: A void pointer for the data to be added to the head of the linkedlist
//
// Returns 0 if the insertion was successful; non-zero for failure.
int InsertLinkedList(LinkedList list, void* data) {
  if (list == NULL) {
    return -1;
  } else {
    LinkedListNodePtr node = CreateLinkedListNode(data);
    if (list->head != NULL) {
      list->head->prev = node;
      node->next = list->head;
      list->head = node;
      list->num_elements += 1;
    } else {
      list->head = node;
      list->tail = node;
      list->num_elements += 1;
    }
    return 0;
  }
}

// Gets the number of elements in the LinkedList
//
// INPUT: A linkedlist whose number of elements you want to obtain
//
// Returns the number of elements in the linkedlist
int NumElemsInLinkedList(LinkedList list) { return list->num_elements; }
