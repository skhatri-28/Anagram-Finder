# Anagram Finder

## Objectives

* Write a program to find anagrams using hashtables
* Write a good C project

## Overview

This program imports a file of strings and uses a hashtable as a map to identify the anagrams
in the file. There is functionality to print the hashtable and the anagrams.

## Details
This program consists of the following files:  
  + FileProcessor.h - A header file defining the method declarations to run various file processing methods related to inputting from the file and outputting to the terminal 
  + FileProcessor.c - A program containing all of the methods to run various file processing methods related to inputting from the file and outputting to the terminal 
  + LinkedList.h - A header file defining the method declarations to implement a Linked List
  + LinkedList.c - A program containing all of the methods to implement a linked list
  + Hashtable.h - A header file defining all the method declarations to implement a Hashtable
  + Hashtable.c - A program containing all of the methods to implement a Hashtable
  + main.c - A program that prints the anagrams and serves as the main entry point to the rest of the program
  + Makefile - This file contains commands for the compiler
  + words.txt - The text file containing anagrams that is to be read in by the program
  + test_hashtable.cc - A test file to unit test the code using Google Test
  + Assert007.h - A header file containing methods to assist in conducting unit tests
  + Assert007.c - A program containing methods to assist in conducting unit tests

## How to Build and Run the Code

#### Compilation
To compile, call "make hashtable."

#### Execute run
The execute, call "make run"

#### Compile and Execute Run
To compile and execute the run, call "make all"

#### Run tests
To run tests, call "make test_suite," followed by "./test_suite"

#### Remove the executable

The executable can be removed by calling "make clean"

### Input

+ words.txt

### Output

List containing sublists of anagrams. Only words in the file that have an anagram will be printed. If a second word is not found that is an anagram of the first, the word will not be printed.

## Additional Notes

I took a trial and error approach with this project. Rather than compute the load factor, resize the hashtable, and copy over elements repeatedly, I started with a sufficiently sized hashtable. Thereafter I tried to come up with my own hash function using a very large prime number that would produce enough variation to result in an approximately even distribution of values. I assessed the hashtable performance by printing the hashtable to see how evenly distributed values were amongst different buckets with my different hashcode functions. If a particular hashcode function didn't produce an even distribution, I kept trying to modify the function until I got a roughly even distribution. I also assessed performance based on how quickly output was generated.
