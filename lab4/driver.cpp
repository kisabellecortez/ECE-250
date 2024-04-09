// include libraries here
#include <iostream>
#include <string>
#include "graph.h"


int main(){
    
    // your code goes here... 

    Graph graph; 
    bool running = true; 

    while(running){
        string cmd; 

        cin >> cmd; 

        if(cmd == "insert"){
            int a, b; 
            double d, s; 

            cin >> a >> b >> d >> s; 

            graph.insert(a, b, d, s);

            cout << "success" << endl; 
        }
        else if(cmd == "load"){
            string filename; 

            cin >> filename; 

            graph.load(filename); 

            cout << "success" << endl; 
        }
        else if(cmd == "traffic"){
            int a, b; 
            double A; 

            cin >> a >> b >> A; 

            if(graph.traffic(a, b, A)){
                cout << "success" << endl; 
            }
            else{
                cout << "failure" << endl; 
            }
        }
        else if(cmd == "update"){
            string filename; 

            cin >> filename; 

            graph.update(filename); 
        }
        else if(cmd == "print"){
            int a; 

            cin >> a; 

            graph.print(a); 
        }
        else if(cmd == "delete"){
            int a; 

            cin >> a; 

            graph.del(a); 
        }
        else if(cmd == "path"){
            int a, b; 

            cin >> a >> b; 

            graph.path(a, b); 
        }
        else if(cmd == "lowest"){
            int a, b; 

            cin >> a >> b; 

            graph.lowest(a, b);
        }
        else if(cmd == "exit"){
            running = false; 
        }
        else{

        }
    } 

}
