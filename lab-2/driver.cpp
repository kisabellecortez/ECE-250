// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"
#include <fstream>

using namespace std;

int main()
{

    // your code goes here...
    Trie trie;

    bool isRunning = true;

    while (isRunning)
    {
        string cmd;
        string input;

        cin >> cmd;

        if (cmd == "load")
        {
            ifstream corpus("corpus.txt");
            string word;

            if (!corpus.is_open()){
                cout << "not open"; 
            }
                while (corpus >> word)
                {
                    trie.insert(word);
                }

            corpus.close();

          cout << "success" << endl; 
        }
        else if (cmd == "i")
        {
            cin >> input;

          bool success = trie.insert(input);

          if(success){
            cout << "success" << endl; 
          }
          else{
            cout << "failure" << endl; 
          }
        }
        else if (cmd == "c")
        {
            cin >> input;

            int count = trie.prefix(input);
          cout << "count is " << count << endl; 
          
        }
        else if (cmd == "e")
        {
            cin >> input;

           trie.erase(input);

            
        }
        else if (cmd == "p")
        {
            trie.print();
        }
        else if (cmd == "spellcheck")
        {
            cin >> input;

            trie.spellCheck(input);
        }
        else if (cmd == "empty")
        {
            trie.isEmpty();
        }
        else if (cmd == "clear") // done
        {
            trie.clear();
        }
        else if (cmd == "size")
        { // done
            trie.size();
        }
        else if (cmd == "exit") // done
        {
            isRunning = false;
        }
    }
}