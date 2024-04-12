#include <iostream>

using namespace std;

// define your classes here...

class Node {
public:
  // member variables
  Node *children[26]; // array of children
  bool isEnd;         // end of word
  Node *parent;

  // initialize constructors
  Node() : isEnd{false} {}
};

class Trie {
private:
  // member variables
  Node *root;
  int numWords;

public:
  // constructor, destructor, member functions
  Trie();
  ~Trie();
  bool insert(string &word);
  int prefix(string &prefix);
  void erase(string &word);
  void print();
  void spellCheck(string &word);
  void isEmpty();
  void clear();
  void size();
  void exit();
  int helperCountWords(Node *node);

  // helper functions
  bool searchWord(string &word);
  bool searchPrefix(string &word);
  bool checkChildren(Node *node);
  char findChar(int &i);
  int findIndex(char &character);
  void recursiveDel(Node *node);
  void recursePrint(Node *node, string &word);
  void recurseClear(Node *node);
  int recursePrefix(Node *node); 
};