/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdio.h>
#include "Hashtable.h"
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

// Allocates and returns a new Hashtable.
//
// INPUT:
//   numBuckets: The number of buckets this hashtable will start with.
//
// Returns a Hashtable or NULL if the hashtable was unable to be malloc'd.
Hashtable CreateHashtable(int num_buckets) {
  Hashtable ht = (Hashtable)malloc(sizeof(struct hashtableInfo));
  if (ht != NULL) {
    ht->num_buckets = num_buckets;
    ht->num_elements = 0;
    ht->buckets = (LinkedList*)malloc(sizeof(LinkedList) * num_buckets);
    int i;
    for (i = 0; i < num_buckets; i++) {
      ht->buckets[i] = NULL;
    }
    return ht;
  } else {
    return NULL;
  }
}

// Destroys and Frees the hashtable.
//
// Input:
//   ht: the table to be free'd. It is unsafe to use the
//    hashtable after this is called.
//
void DestroyHashtable(Hashtable ht) {
  int i;
  for (i = 0; i < ht->num_buckets; i++) {
    if (ht->buckets[i] != NULL) {
      LinkedListNodePtr cur_node = ht->buckets[i]->head;
      while (cur_node != NULL) {
        HTKeyValuePtr anagram_data = (HTKeyValuePtr)cur_node->data;
        LinkedList anagrams_list = anagram_data->value;
        DestroyLinkedList(anagrams_list);
        free(anagram_data->key);
        cur_node = cur_node->next;
      }
      DestroyLinkedList(ht->buckets[i]);
    }
  }
  free(ht->buckets);
  free(ht);
}

// Puts the given key value pair into the hashtable.
//
// INPUT:
//   ht: the hashtable to insert into
//   sortedWord: the key to insert into the hashtable (i.e a sorted
//   word used as an identifier for an anagram)
//   word: the value to insert into the hashtable (i.e. the word that is an
// anagram)
//
void InsertInHashtable(Hashtable ht, char* sorted_word, char* word) {
  int64_t bucket_number = hash(sorted_word) % ht->num_buckets;
  if (HTContainsAnagramIdentifier(ht, bucket_number, sorted_word)) {
    LinkedListNodePtr cur_node = ht->buckets[bucket_number]->head;
    while (cur_node != NULL) {
      HTKeyValuePtr anagram_data = (HTKeyValuePtr)cur_node->data;
      LinkedList anagrams = anagram_data->value;
      if ((strcmp(anagram_data->key, sorted_word) == 0) &&
          !(NotInList(anagrams, word))) {
        char* anagram = (char*)malloc(sizeof(*word) * (strlen(word) + 1));
        strncpy(anagram, word, strlen(word) + 1);
        InsertLinkedList(anagrams, anagram);
      }
      cur_node = cur_node->next;
    }
  } else {
    if (ht->buckets[bucket_number] == NULL) {
      ht->buckets[bucket_number] = CreateLinkedList();
    }
    HTKeyValuePtr anagram_data = (HTKeyValuePtr)malloc(sizeof(HTKeyValue));
    char* anagram_identifier =
        (char*)malloc(sizeof(*sorted_word) * (strlen(sorted_word) + 1));
    strncpy(anagram_identifier, sorted_word, strlen(sorted_word) + 1);
    anagram_data->key = anagram_identifier;
    LinkedList anagrams = CreateLinkedList();
    anagram_data->value = anagrams;
    char* anagram = (char*)malloc(sizeof(*word) * (strlen(word) + 1));
    strncpy(anagram, word, strlen(word) + 1);
    InsertLinkedList(anagrams, anagram);
    ht->num_elements += 1;
    InsertLinkedList(ht->buckets[bucket_number], anagram_data);
  }
}

// Checks whether a given anagram exists in the Hashtable
//
// INPUT:
//  ht: the hashtable to look in for the given anagram
//  bucket: the array number returned by the hash function
//  sortedWord: the key to search for in the hashtable (i.e. the identifier for
//  an anagram)
//  word: the anagram which the user is searching for
//
bool NotInList(LinkedList anagram_list, char* word) {
  LinkedListNodePtr anagram_list_cur_node = anagram_list->head;
  while (anagram_list_cur_node != NULL) {
    if (strcmp((char*)anagram_list_cur_node->data, word) == 0) {
      return true;
    }
    anagram_list_cur_node = anagram_list_cur_node->next;
  }
  return false;
}

// Checks whether a given anagram identifier(i.e. key) exists in the Hashtable
//
// INPUT:
//  ht: the hashtable to look in for the given anagram identifier(i.e. key)
//  bucket: the array number returned by the hash function
//  sortedWord: the anagram identifier to search for in the hashtable (i.e. the
// key)
//
bool HTContainsAnagramIdentifier(Hashtable ht, int64_t bucket,
                                 char* sorted_word) {
  if (ht->buckets[bucket] != NULL) {
    LinkedListNodePtr cur_node = ht->buckets[bucket]->head;
    while (cur_node != NULL) {
      HTKeyValuePtr anagram_data = (HTKeyValuePtr)cur_node->data;
      if (strcmp(anagram_data->key, sorted_word) == 0) {
        return true;
      }
      cur_node = cur_node->next;
    }
  }
  return false;
}

// Gets the number of elements in the Hashtable
//
// INPUT:
//  ht: the hashtable to get the number of elements from
//
//  Returns the number of elements in the Hashtable
int NumElemsInHashtable(Hashtable ht) { return ht->num_elements; }

// Hash function for a Hashtable, uses the string positions, ASCII values, and
// a large prime number to compute a hash function
//
// INPUT:
//  key: the key to insert in the hashtable which determines
//       the output of the hash function
//
int64_t hash(char* key) {
  char* c;
  const int64_t kLargePrime = 331319UL;
  const int64_t kVarianceModifier = 17;
  int sum = 0;
  int position = 1;
  for (c = key; *c != '\0'; c++) {
    int64_t value = *c * position;
    sum += value;
    position += kVarianceModifier;
  }
  return sum * kLargePrime;
}

// Returns the value associated with a given key in the hashtable.
// If the key does not exist, the function returns null
//
// INPUT:
//  ht: the hashtable to search for the key in
//  sortedWord: the key whose value is to be found (i.e. the identifier for an
//  anagram)
//
// Returns a list of anagrams, if there are no anagrams for the given key, null
// is returned
LinkedList GetInHashtable(Hashtable ht, char* sorted_word) {
  int bucket_number = hash(sorted_word) % ht->num_buckets;
  if (ht->buckets[bucket_number] != NULL) {
    LinkedListNodePtr cur_node = ht->buckets[bucket_number]->head;
    while (cur_node != NULL) {
      HTKeyValuePtr anagram_data = (HTKeyValuePtr)cur_node->data;
      if (strcmp(anagram_data->key, sorted_word) == 0) {
        return anagram_data->value;
      }
      cur_node = cur_node->next;
    }
  }
  return NULL;
}

// Prints a hashtable
//
// INPUT:
//  ht: the hashtable to print
//
void PrintHashtable(Hashtable ht) {
  printf("HT has %d buckets\nHT has %d elements\n", ht->num_buckets,
         ht->num_elements);
  int i;
  for (i = 0; i < ht->num_buckets; i++) {
    printf("Bucket %d: ", i);
    if (ht->buckets[i] != NULL) {
      LinkedListNodePtr cur_node = ht->buckets[i]->head;
      printf("\n");
      while (cur_node != NULL) {
        HTKeyValuePtr anagram_data = (HTKeyValuePtr)cur_node->data;
        printf("\tkey: %s\tvalue: [", anagram_data->key);
        LinkedListNodePtr anagram_list_cur_node = anagram_data->value->head;
        while (anagram_list_cur_node->next != NULL) {
          char* anagram = (char*)anagram_list_cur_node->data;
          printf("%s,", anagram);
          anagram_list_cur_node = anagram_list_cur_node->next;
        }
        printf("%s],\n", (char*)anagram_list_cur_node->data);
        cur_node = cur_node->next;
      }
    } else {
      printf("NULL\n");
    }
  }
  printf("\n");
}

