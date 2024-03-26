#include "tokenize.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <sstream>
#include <vector>
#include <forward_list>

// implement classes' member functions here...

/* HASH TABLE FUNCTIONS - done */

/* constructor - done */
HashTable::HashTable()
{
    numWords = 0;
}

/* destructor - done */
HashTable::~HashTable()
{
    for (int i = 0; i < sizeArray; i++)
    {
        for (auto &node : toTok[i])
        {
            delete node;
        }
    }

    delete[] toTok;
    delete[] toWord;
}

/* PROJECT FUNCTIONS */

/* create hash table of input size - done */
void HashTable::create(unsigned &size)
{
    toTok = new forward_list<Node *>[size];
    toWord = new string[size];
    sizeArray = size;
    loadFactor = numWords / sizeArray;
}

/* insert word into hash table - done */
bool HashTable::insert(string &word)
{
    unsigned length = word.length();
    char wordArray[word.length() + 1];
    strcpy(wordArray, word.c_str());

    // check if word only contains alphabet
    if (!isAlphabetic(wordArray, length))
    {
        return false;
    }

    // rehash if load factor is greater than 80%
    if (loadFactor >= 0.8)
    {
        rehashFunction();
    }

    // see if word exists
    for (int i = 0; i < numWords; i++)
    {
        if (toWord[i] == word)
        {
            return false;
        }
    }

    // add word to linked list if it doesn't exist

    // create new word
    unsigned key = hashFunction(word);
    Node *newNode = new Node(word, numWords + 1);

    // add to front of linked list
    toTok[key].push_front(newNode);

    // add word to token to word array
    toWord[numWords] = word;

    ++numWords;

    loadFactor = static_cast<double>(numWords) / static_cast<double>(sizeArray);

    return true;
}

/* insert words in file into hash table - done */
bool HashTable::load(string &filename)
{
    ifstream file(filename);
    string word;
    bool isLoaded = false;

    while (file >> word)
    {
        if (insert(word))
        {
            isLoaded = true;
        }
    }

    file.close();

    return isLoaded;
}

/* return token of input word - done */
int HashTable::tok(string &word)
{
    // convert string to char array
    unsigned length = word.length();
    char wordArray[word.length() + 1];
    strcpy(wordArray, word.c_str());

    // if not alphabetic
    if (!isAlphabetic(wordArray, length))
    {
        return -1;
    }

    unsigned key = hashFunction(word);

    // print key if word exists
    for (auto &node : toTok[key])
    {
        if (node->word == word)
        {
            return node->key;
        }
    }

    return -1;
}

/* return word of input tok - done */
string HashTable::ret(int &tok)
{
    // see if token is out of the array or
    if (tok < 0 || tok > numWords)
    {
        return "N/A";
    }
    else
    {
        return toWord[tok - 1];
    }
}

/* return tokens of all words - done */
void HashTable::tok_all(string &words)
{
    istringstream wordsArray(words);
    string word;

    // print tokens of all words in string words
    while (wordsArray >> word)
    {
        cout << tok(word) << " ";
    }

    cout << endl;
}

/* return words of all tokens - done */
void HashTable::ret_all(string &toks)
{
    istringstream toksArray(toks);
    string tokS;

    // print words of all tokens in string toks
    while (toksArray >> tokS)
    {
        try
        {
            int tok = stoi(tokS);
            cout << ret(tok) << " ";
        }
        catch (exception e)
        {
            cout << "N/A ";
        }
    }

    cout << endl;
}

/* print chain - done */
void HashTable::print(unsigned &k)
{
    for (auto &node : toTok[k])
    {
        cout << node->word + " ";
    }

    cout << endl;
}

/* HELPER FUNCTIONS */

/* hashing function - done */
unsigned HashTable::hashFunction(const string &str)
{
    unsigned ans = 0;

    for (auto it = str.begin(); it != str.end(); ++it)
    {
        ans = ans * 29 + *it;
    }

    unsigned hash = ans % sizeArray;

    return hash;
}

/* rehash hash table */
void HashTable::rehashFunction()
{
    // Save old hash table
    unsigned oldSize = sizeArray;
    forward_list<Node *> *oldToTok = toTok;
    string *oldToWord = toWord;

    // Create new hash table
    sizeArray *= 2;
    toTok = new forward_list<Node *>[sizeArray];
    toWord = new string[sizeArray];

    // Loop through old hash table
    for (unsigned i = 0; i < oldSize; i++)
    {
        for (auto &node : oldToTok[i])
        {
            unsigned key = hashFunction(node->word);
            Node *newNode = new Node(node->word, node->key);
            toTok[key].push_front(newNode);
            toWord[node->key - 1] = node->word;
        }
    }

    delete[] oldToTok;
    delete[] oldToWord;

    loadFactor = static_cast<double>(numWords) / static_cast<double>(sizeArray);
}

/* checks if string is alphabetic */
bool HashTable::isAlphabetic(char word[], unsigned &size)
{
    for (int i = 0; i < size; i++)
    {
        if (!isalpha(word[i]))
        {
            return false;
        }
    }

    return true;
}