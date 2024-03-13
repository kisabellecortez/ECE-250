#include "trie.h"
#include <cstring>
#include <iostream>
#include <string>

// implement classes' member functions here...

// constructor - done
Trie::Trie()
{
    root = new Node();
    numWords = 0;
}

// destructor
Trie::~Trie() {}

// insert word into trie - done
bool Trie::insert(string word)
{
    Node *curr{root};
    Node *prev{nullptr};

    // create array of chars of given word
    int length = word.length();
    char wordArray[length + 1];
    strcpy(wordArray, word.c_str());

    // if word doesn't exist
    if (!searchWord(word))
    {

        // find children that don't exist
        for (int i = 0; i < length; i++)
        {
            int indexToSearch = findIndex(wordArray[i]); // returns index of character

            // add child if it doesn't exist
            if (curr->children[indexToSearch] == nullptr)
            {
                Node *nodeToAdd = new Node(); // create new node
                curr->children[indexToSearch] =
                    nodeToAdd;            // store address of new node to array at index
                nodeToAdd->parent = curr; // store the parent of the new node

                // indicate end of word if final character
                if (i == length - 1)
                {
                    nodeToAdd->isEnd = true;
                }
            }
            else if (i == length - 1)
            {
                curr->children[indexToSearch]->isEnd = true;
            }
            prev = curr;
            curr = curr->children[indexToSearch]; // go to next node
        }
        numWords++; // add word
        return true;
    }
    else
    {
        return false;
    }
}

// find all words beginning with prefix
int Trie::prefix(string prefix)
{
    Node *curr{root};

    int length = prefix.length();
    char *prefixArray = new char[length + 1];
    strcpy(prefixArray, prefix.c_str());

    // loop through Trie to find prefix
    for (int i = 0; i < length; i++)
    {
        int indexToSearch = findIndex(prefixArray[i]);

        if (curr->children[indexToSearch] == nullptr)
        {
            return 0;
        }

        curr = curr->children[indexToSearch];
    }

    return recursePrefix(curr);
}

// erase word - done
void Trie::erase(string word)
{
    Node *curr{root};
    Node *prev{nullptr};

    int length = word.length();
    char wordArray[length + 1];
    strcpy(wordArray, word.c_str());

    // check if word exists
    if (searchWord(word))
    {
        // go to end of the word
        for (int i = 0; i < length; i++)
        {
            int index = findIndex(wordArray[i]); // find index of character

            prev = curr;
            curr = curr->children[index]; // go to next node
        }

        // if end of word has children change node to not end of word
        if (curr->isEnd && checkChildren(curr))
        {
            curr->isEnd = false;
        }
        // recursively delete parent node
        else
        {
            for (int i = 0; i < 26; i++)
            {
                if (prev->children[i] == curr)
                {
                    prev->children[i] = nullptr;
                    delete curr;
                    break;
                }
            }
            recursiveDel(prev);
        }

        numWords--; // delete word
        cout << "success" << endl;
    }
    else
    {
        cout << "failure" << endl;
    }
}

// print all words - done
void Trie::print()
{
    // print words if tree is not empty
    if (checkChildren(root))
    {
        string word = "";
        recursePrint(root, word);
        cout << endl;
    }
}

// print if word is in trie, otherwise suggest words with prefix - done
void Trie::spellCheck(string prefix)
{
    Node *curr{root};

    // create char array of prefix
    int length = prefix.length();
    char *prefixArray = new char[length + 1];
    strcpy(prefixArray, prefix.c_str());

    // check if word exists
    if (!searchWord(prefix))
    {
        string maxPrefix = ""; // start with empty prefix

        // find max prefix
        for (int i = 0; i < length; i++)
        {
            int indexToSearch = findIndex(prefixArray[i]);

            // check if letter exists
            if (curr->children[indexToSearch] != nullptr)
            {
                maxPrefix += prefixArray[i];
                curr = curr->children[indexToSearch]; // go to node of next letter
            }
            else
            {
                break;
            }
        }

        recursePrint(curr, maxPrefix); // recursively print words with prefix
        cout << endl;
    }
    else
    {
        cout << "correct" << endl;
    }
}

// check if trie is empty - done
void Trie::isEmpty()
{
    // empty
    if (numWords == 0)
    {
        cout << "empty 1" << endl;
    }
    // not empty
    else
    {
        cout << "empty 0" << endl;
    }
}

// clear all nodes
void Trie::clear()
{
    // delete tree if it isn't empty
    if (checkChildren(root))
    {
        recurseClear(root);
    }

    numWords = 0;

    cout << "success" << endl;
}

// print number of words - done
void Trie::size() { cout << "number of words is " << numWords << endl; }

/*          helper functions          */

// search for word - done
bool Trie::searchWord(string word)
{
    Node *curr{root};
    bool isFound = false;
    bool iterate = true;
    int i = 0;

    // turn word into an array of characters
    int length = word.length();
    char *wordArray = new char[length + 1];
    strcpy(wordArray, word.c_str());

    // loop through trie
    while (iterate)
    {
        int index = findIndex(wordArray[i]); // find index of character

        // check if there is a node for each index
        if (curr->children[index] != nullptr)
        {

            if (curr->children[index] != nullptr)
            {
                // check if it's the end of the word
                if (i == length - 1)
                {
                    if (curr->children[index]->isEnd == true)
                    {
                        isFound = true;
                    }

                    iterate = false;
                }
            }
        }
        // there is no node corresponding to at least 1 index;
        else
        {
            iterate = false;
        }

        curr = curr->children[index];
        i++;
    }

    return isFound;
}

bool Trie::searchPrefix(string prefix)
{
    Node *curr{root};
    bool isFound = false;
    bool iterate = true;
    int i = 0;

    // turn word into an array of characters
    int length = prefix.length();
    char *prefixArray = new char[length + 1];

    // loop through trie
    while (iterate)
    {
        int index = findIndex(prefixArray[i]); // find index of character

        // check if there is a node for each index
        if (curr->children[index] != nullptr)
        {
            // check if it's the end of the word
            if (i == length - 1)
            {
                isFound = true;
                iterate = false;
            }
        }
        // there is no node corresponding to at least 1 index;
        else
        {
            iterate = false;
        }

        i++;
    }

    return isFound;
}

// check if node has children
bool Trie::checkChildren(Node *node)
{
    bool children = false;

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
        {
            children = true;
        }
    }

    return children;
}

// find character of given index
char Trie::findChar(int i)
{
    char array[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                      'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                      'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    return array[i];
}

// find index of given character - done
int Trie::findIndex(char character)
{
    int index = -1;
    char array[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                      'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                      'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (int i = 0; i < 26; i++)
    {
        if (array[i] == character)
        {
            index = i;
            break;
        }
    }

    return index;
}

void Trie::recursiveDel(Node *node)
{
    // don't delete if node has children
    if (checkChildren(node))
    {
    }
    else if (node->isEnd)
    {
    }
    // recursively delete if node has no children
    else
    {
        Node *parent = node->parent;

        // find char of node
        for (int i = 0; i < 26; i++)
        {
            if (parent->children[i] == node)
            {
                parent->children[i] = nullptr;
            }
        }

        delete node;

        recursiveDel(parent);
    }
}

void Trie::recursePrint(Node *node, string &word)
{
    if (node == nullptr)
    {
    }
    else if (node->isEnd)
    {
        cout << word + " ";

        if (checkChildren(node))
        {
            for (int i = 0; i < 26; i++)
            {
                if (node->children[i] != nullptr)
                {
                    word.push_back(findChar(i));
                    recursePrint(node->children[i], word);
                    word.pop_back();
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                word.push_back(findChar(i));
                recursePrint(node->children[i], word);
                word.pop_back();
            }
        }
    }
}

void Trie::recurseClear(Node *node)
{
    if (node == nullptr)
    {
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
            {
                recurseClear(node->children[i]);
                delete node->children[i];
                node->children[i] = nullptr;
            }
        }
    }
}

int Trie::recursePrefix(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        int count;

        if (node->isEnd)
        {
            count = 1;
        }
        else
        {
            count = 0;
        }

        for (int i = 0; i < 26; i++)
        {
            count += recursePrefix(node->children[i]);
        }

        return count;
    }
}