/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FileProcessor.h"
#include "LinkedList.h"

// Identifies the number of lines in the file
//
// INPUT: the filename to search
//
// Returns the number of lines in the file or -1
// if file cannot be read
int GetNumLinesInFile(char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File doesn't exist");
    return -1;
  } else {
    char line_input[100];
    int line_count = 0;
    while (fgets(line_input, sizeof(line_input), fp)) {
      line_count++;
    }
    fclose(fp);
    return line_count;
  }
}

// Reads each word in the file and adds it to a hashtable using the
// sorted word as the key
//
// INPUT:
//  ht: the hashtable to add the word in
//  filename: the filename of the file to read the words in from
//
void Readfile(Hashtable ht, char* filename) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("File not found");
  } else {
    char line_input[100];
    while (fgets(line_input, sizeof(line_input), fp)) {
      int line_length = strcspn(line_input, "\n");
      line_input[line_length] = '\0';
      char* word = (char*)malloc(sizeof(*word) * (line_length + 1));
      char* sorted_word =
          (char*)malloc(sizeof(*sorted_word) * (line_length + 1));
      strncpy(word, line_input, strlen(line_input) + 1);
      strncpy(sorted_word, word, strlen(line_input) + 1);
      SortString(sorted_word);
      InsertInHashtable(ht, sorted_word, word);
      free(word);
      free(sorted_word);
    }
  }
  fclose(fp);
}

// Sorts the characters in a string in alphabetical order
//
// INPUT:
//  string: an array of characters containing the string to be sorted
//
void SortString(char* string) {
  int i;
  int j;
  int n = strlen(string);
  char temp;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (string[i] > string[j]) {
        temp = string[i];
        string[i] = string[j];
        string[j] = temp;
      }
    }
  }
}

// Prints the anagrams from a hashtable
//
// INPUT:
//  ht: the hashtable to print the anagrams from
//
void PrintAnagrams(Hashtable ht) {
  const int kRequiredWords = 2;
  int i;
  printf("[");
  for (i = 0; i < ht->num_buckets; i++) {
    if (ht->buckets[i] != NULL) {
      LinkedListNodePtr cur_node = ht->buckets[i]->head;
      while (cur_node != NULL) {
        HTKeyValuePtr anagram_data = (HTKeyValuePtr)cur_node->data;
        LinkedList anagram_list = anagram_data->value;
        if (anagram_list->num_elements >= kRequiredWords) {
          LinkedListNodePtr anagram_list_cur_node = anagram_data->value->head;
          if (i != ht->num_buckets - 1) {
            printf(", [");
            while (anagram_list_cur_node->next != NULL) {
              char* anagram = (char*) anagram_list_cur_node->data;
              printf("%s,", anagram);
              anagram_list_cur_node = anagram_list_cur_node->next;
            }
            printf("%s]", (char*) anagram_list_cur_node->data);
          }
        }
        cur_node = cur_node->next;
      }
    }
  }
  printf("]\n");
}

