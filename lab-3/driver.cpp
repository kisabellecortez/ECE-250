// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"
#include <sstream>
#include <vector>

using namespace std;

int main()
{

    // your code goes here...

    // variables for conditions
    bool running = true;
    bool hashCreated = false;

    HashTable ht; 

    while (running)
    {
        // variables for inputs
        string cmd;
        string param_s;
        int param_n;

        cin >> cmd; // get input command

        /* run function for command */

        /* create hash table with size - done */
        if (cmd == "create" && !hashCreated)
        { 
            // run create function with input size
            cin >> param_n;

            if (param_n < 1)
            {
            }
            else
            {
                unsigned size = param_n; 
                ht.create(size);  // create a hash table object with input size
                hashCreated = true;

                cout << "success" << endl; 
            }
        }

        /* insert word in dictionary - done */
        else if (cmd == "insert" && hashCreated)
        {
            // run insert function with input word
            cin >> param_s;

            bool isInserted = ht.insert(param_s);

            if (isInserted)
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }

        /* insert all words in file - done */
        else if (cmd == "load" && hashCreated)
        {
            // run load function with input filename
            cin >> param_s;

            bool isLoaded = ht.load(param_s);

            if (isLoaded)
            {
                cout << "success" << endl;
            }
            else
            {
                cout << "failure" << endl;
            }
        }
        else if (cmd == "tok" && hashCreated)
        {
            // run tok function with input word
            cin >> param_s;

            int token = ht.tok(param_s);

            cout << token << endl; 
        }
        else if (cmd == "ret" && hashCreated)
        {
            // run ret function with input token
            cin >> param_n;

            ht.ret(param_n); 
        }
        else if (cmd == "tok_all" && hashCreated)
        {
            // run tok_all function with input words
            getline(cin, param_s); 

            ht.tok_all(param_s); 
        }
        else if (cmd == "ret_all" && hashCreated)
        {
            // run ret_all function with input tokens
            getline(cin, param_s); 

            ht.ret_all(param_s); 
        }
        else if (cmd == "print" && hashCreated)
        {
            // run print function with input k
            cin >> param_n;
            unsigned index = param_n; 

            ht.print(index); 
        }
        else if (cmd == "exit")
        {
            running = false;
        }
    }
}