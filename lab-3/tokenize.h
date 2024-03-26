#include <string>
#include <forward_list>

using namespace std;

// define your classes here...

class Node
{
public:
    /* member variables */
    string word;
    unsigned key;
    Node *next;

    /* class functions */
    Node(string newWord, unsigned newKey) : word{newWord}, key{newKey}, next{nullptr} {};
};

class HashTable
{
public:
    /* class functions */
    HashTable();
    ~HashTable();

    /* project functions */
    void create(unsigned &size);
    bool insert(string &word);
    bool load(string &filename);
    int tok(string &word);
    string ret(int &tok);
    void tok_all(string &words);
    void ret_all(string &toks);
    void print(int &k);

    /* helper functions */
    unsigned hashFunction(const string &str);
    void rehashFunction();
    string toUppercase(char str[], unsigned &length);
    bool isAlphabetic(char word[], unsigned &size);

private:
    forward_list<Node *> *toTok; // word to token hash table
    string *toWord;              // token to word hash table
    unsigned sizeArray;
    unsigned numWords;
    double loadFactor;
};