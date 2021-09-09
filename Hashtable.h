/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdint.h>
#include <stdbool.h>
#include "LinkedList.h"
#include <stdint.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H

// Hashtable consists of an array containing
// buckets whereby each bucket points to a
// linkedlist
struct hashtableInfo {
  int num_buckets;
  int num_elements;
  LinkedList* buckets;
};

typedef struct hashtableInfo* Hashtable;

// Hashtable stores key value pairs whereby the key is a string
// and the value is a linkedlist of strings
typedef struct {
  char* key;         // the key in the key/value pair
  LinkedList value;  // the value in the key/value pair
} HTKeyValue, *HTKeyValuePtr;

// Allocates and returns a new Hashtable.
//
// INPUT:
//   numBuckets: The number of buckets this hashtable will start with.
//
// Returns a Hashtable or NULL if the hashtable was unable to be malloc'd.
Hashtable CreateHashtable(int num_buckets);

// Destroys and Frees the hashtable.
//
// Input:
//   ht: the table to be free'd. It is unsafe to use the
//    hashtable after this is called.
//
void DestroyHashtable(Hashtable ht);

// Puts the given key value pair into the hashtable.
//
// INPUT:
//   ht: the hashtable to insert into
//   sortedWord: the key to insert into the hashtable (i.e a sorted
//   word used as an identifier for an anagram)
//   word: the value to insert into the hashtable (i.e. the word that is an
// anagram)
//
void InsertInHashtable(Hashtable ht, char* sorted_word, char* word);

// Checks whether a given anagram exists in the Hashtable
//
// INPUT:
//  ht: the hashtable to look in for the given anagram
//  bucket: the array number returned by the hash function
//  sortedWord: the key to search for in the hashtable (i.e. the identifier for
//  an anagram)
//  word: the anagram which the user is searching for
//
bool NotInList(LinkedList anagrams_list, char* word);

// Checks whether a given anagram identifier(i.e. key) exists in the Hashtable
//
// INPUT:
//  ht: the hashtable to look in for the given anagram identifier(i.e. key)
//  bucket: the array number returned by the hash function
//  sortedWord: the anagram identifier to search for in the hashtable (i.e. the
// key)
//
bool HTContainsAnagramIdentifier(Hashtable ht, int64_t bucket,
                                 char* sorted_word);

// Hash function for a Hashtable, uses the string positions, ASCII values, and
// a large prime number to compute a hash function;
//
// INPUT:
//  key: the key to insert in the hashtable which determines
//       the output of the hash function
//
int64_t hash(char* key);

// Gets the number of elements in the Hashtable
//
// INPUT:
//  ht: the hashtable to get the number of elements from
//
//  Returns the number of elements in the Hashtable
int NumElemsInHashtable(Hashtable ht);

// Returns the value associated with a given key in the hashtable.
// If the key does not exist, the function returns null
//
// INPUT:
//  ht: the hashtable to search for the key in
//  sortedWord: the key whose value is to be found (i.e. the identifier for an
//  anagram)
//
LinkedList GetInHashtable(Hashtable ht, char* sorted_word);

// Prints a hashtable
//
// INPUT:
//  ht: the hashtable to print
//
void PrintHashtable(Hashtable ht);

#endif  // HASHTABLE_H

