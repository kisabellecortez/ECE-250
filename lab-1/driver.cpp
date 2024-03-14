// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "game.h"

using namespace std;

int main()
{

    // your code goes here...

    LinkedList list; // initialize linked list

    string cmd;
    bool isPlaying = true;

    cin >> cmd;

    while (isPlaying)
    {
        if (cmd == "SPAWN")
        {
            double x; 
            double y;

            cin >> x;
            cin >> y;

            list.spawn(x, y);
        }

        if (cmd == "PRT")
        {
            double d;

            cin >> d;

            list.prt(d);
        }
        else if (cmd == "TIME")
        {
            double t;

            cin >> t;

            list.time(t);
        }
        else if (cmd == "LUNCH")
        {
            list.lunch();
        }
        else if (cmd == "NUM")
        {
            list.num();
        }
        else if (cmd == "OVER")
        {
            list.over();
            isPlaying = false;
        }
        else
        {
        }

        cin >> cmd;

    }
    return 0;
}