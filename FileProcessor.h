/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdio.h>
#include "Hashtable.h"

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

// Identifies the number of lines in the file
//
// INPUT: the filename to search
//
// Returns the number of lines in the file or -1
// if file cannot be read
int GetNumLinesInFile(char* filename);

// Reads each word in the file and adds it to a hashtable using the
// sorted word as the key
//
// INPUT:
//  ht: the hashtable to add the word in
//  filename: the filename of the file to read the words in from
//
void Readfile(Hashtable ht, char* filename);

// Sorts the characters in a string in alphabetical order
//
// INPUT:
//  string: an array of characters containing the string to be sorted
//
void SortString(char* string);

// Prints the anagrams from a hashtable
//
// INPUT:
//  ht: the hashtable to print the anagrams from
//
void PrintAnagrams(Hashtable ht);

#endif  // FILEPROCESSOR_H
