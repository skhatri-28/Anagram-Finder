/**
 *  CS5008  Spr 2021
 *  Northeastern University, Seattle
 *  Assignment 6: Hashtables
 *
 *  Author: Shefali Khatri (03/12/2021);
 */


#include "gtest/gtest.h"
extern "C" {
    #include "Hashtable.h"
    #include "LinkedList.h"
}
const char* first = "first";
const char* second="second";
const char* third = "third";
const char* fourth = "fourth";

#define MAX_VALUE_LEN 75



TEST(Hashtable, Create) {
  Hashtable ht = CreateHashtable(5);
  EXPECT_FALSE(ht == NULL);
  EXPECT_FALSE(ht->buckets == NULL);
  EXPECT_EQ(NumElemsInHashtable(ht), 0);
  DestroyHashtable(ht);
}

TEST(Hashtable, AddOneElemDestroy) {
    Hashtable ht = CreateHashtable(5);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char key[] = "aet";
    char value [] = "eat";
    InsertInHashtable(ht, key, value);

    EXPECT_EQ(NumElemsInHashtable(ht), 1);
 
    DestroyHashtable(ht);
}
//This test has issues when destroying linkedlist.
//To fix this issue, data added to linkedlist must be malloc'ed.
//Mallocing in C++ appears to be different than in C.
TEST(Hashtable, AddOneElemTwoTimes) {
    Hashtable ht = CreateHashtable(5);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    char key[] = "dgo";
    char value[] = "dog";

    InsertInHashtable(ht, key, value);
    //char temp[4];  
    //char* t = malloc(sizeof(char)*4);
    
 
    EXPECT_EQ(NumElemsInHashtable(ht), 1);
   
    // Trying to put it in again should result in no change to number
    InsertInHashtable(ht, key, value);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    // Also want to try a different element with the same key (diff val)
    char key2 [] = "dgo";
    char value2 [] = "god";
  
    InsertInHashtable(ht, key2, value2);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);


    LinkedList expected = CreateLinkedList();
    InsertLinkedList(expected,  value);
    InsertLinkedList(expected,  value2);
    LinkedList result = GetInHashtable(ht, key);
    EXPECT_EQ(NumElemsInLinkedList(result), NumElemsInLinkedList(expected));
    char* expected_value1 = (char*) expected->head->data;
    char* expected_value2 = (char*) expected->head->next->data;
    char* result_value1 = (char*) result->head->data;
    char* result_value2 = (char*) result->head->next->data;
    EXPECT_EQ(strcmp(expected_value1, result_value1), 0);
    EXPECT_EQ(strcmp(expected_value2, result_value2), 0);  
    DestroyHashtable(ht);
}


TEST(Hashtable, AddMultipleItems) {
    Hashtable ht = CreateHashtable(100);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char key1 [] = "acer";
    char value1 [] = "care";
    InsertInHashtable(ht, key1, value1);

    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    char key2 [] = "dgo";
    char value2 [] = "dog";
    InsertInHashtable(ht, key2, value2);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    char key3 [] = "aet";
    char value3 [] = "eat";
    InsertInHashtable(ht, key3, value3);

    ASSERT_EQ(NumElemsInHashtable(ht), 3);

    DestroyHashtable(ht);
}


TEST(Hashtable, GetInHashtable) {
    Hashtable ht = CreateHashtable(4);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char key [] = "aet";
    char value [] = "eat";
    InsertInHashtable(ht, key, value);

    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    char key2 [] = "dgo";
    char value2 [] = "dog";
    InsertInHashtable(ht, key2, value2);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    char key3 [] = "aet";
    char value3 [] = "ate";
    InsertInHashtable(ht, key3, value3);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    // Now, lookup:
    LinkedList result1 = GetInHashtable(ht, key);
    LinkedList result2 = GetInHashtable(ht, key2);
    LinkedList anagram_set1 = CreateLinkedList();
    LinkedList anagram_set2 = CreateLinkedList();
    InsertLinkedList(anagram_set1, value);
    InsertLinkedList(anagram_set1, value3);
    InsertLinkedList(anagram_set2, value2);
    EXPECT_EQ(NumElemsInLinkedList(result1), NumElemsInLinkedList(anagram_set1));
    EXPECT_EQ(NumElemsInLinkedList(result2), NumElemsInLinkedList(anagram_set2));
   
  
    char* result1_word1 = (char*) result1->head->data;
    char* result1_word2 = (char*) result1->head->next->data;
    char* result2_word1 = (char*) result2->head->data;
   
    char* anagram_set1_word1 = (char*) anagram_set1->head->data;
    char* anagram_set1_word2 = (char*) anagram_set1->head->next->data;
    char* anagram_set2_word1 = (char*) anagram_set2->head->data;

    char word [] = "oats";
    EXPECT_TRUE(GetInHashtable(ht, word) == NULL);
 
    EXPECT_EQ(strcmp(result1_word1, anagram_set1_word1), 0);
    EXPECT_EQ(strcmp(result1_word2, anagram_set1_word2), 0);
    EXPECT_EQ(strcmp(result2_word1, anagram_set2_word1), 0);
   
    DestroyHashtable(ht);
}

TEST(LinkedList, InsertingIntoList){
    LinkedList list = CreateLinkedList();
    char value[] = "something";
    InsertLinkedList(list, (char*) value);
}

TEST(Hashtable, TwoElemsOneBucket) {
    Hashtable ht = CreateHashtable(2);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    char key [] = "abbgginr";
    char value [] = "grabbing";
    InsertInHashtable(ht, key, value);

    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    char key2 [] = "gmy";
    char value2 []= "gym";
    InsertInHashtable(ht, key2, value2);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);
    LinkedList result1 = GetInHashtable(ht, key);
    LinkedList expected_output = CreateLinkedList();
    InsertLinkedList(expected_output, value);
    ASSERT_EQ(NumElemsInLinkedList(expected_output), NumElemsInLinkedList(result1));
    char* result_word = (char*) result1->head->data;
    char* expected_word = (char*)expected_output->head->data;
    ASSERT_EQ(strcmp(result_word, expected_word), 0);

    LinkedList result2 = GetInHashtable(ht, key2);
   
    LinkedList expected_output2 = CreateLinkedList();
    InsertLinkedList(expected_output2, value2);
    ASSERT_EQ(NumElemsInLinkedList(result2), NumElemsInLinkedList(expected_output2));
    char* result_word2 = (char*)result2->head->data;
    char* expected_word2 = (char*)expected_output2->head->data;
    ASSERT_EQ(strcmp(result_word2, expected_word2), 0);

    DestroyHashtable(ht);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
