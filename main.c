/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */

#include <stdio.h>
#include "Hashtable.h"

int main() {
  const int kBucketCountDivisor = 20;
  int line_count = GetNumLinesInFile("words.txt");
  Hashtable ht = CreateHashtable(1 + (line_count / kBucketCountDivisor));
  Readfile(ht, "words.txt");
  PrintAnagrams(ht);
  // You can uncomment out the below function if you would
  // like to print all contents of the hashtable
  // PrintHashtable(ht);
  DestroyHashtable(ht);
  return 0;
}
