// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "playlist.h"


int main(int argc, char *argv[]){

    // your code goes here...

    std::string input; 
    std::string cmd; 
    bool playlistInit = false; 
    bool running = true; 

    //get command
    std::getline(std::cin, input); 
    cmd = input.substr(0, input.find(" ")); 

    Playlist myPlaylist; 

    //initializing of playlist only ran once
    if(cmd == "m"){
        int N = stoi(input.substr(2)); 

        myPlaylist = Playlist(N); 

        playlistInit = true; 

<<<<<<< HEAD
        cout << "done" << endl; 
=======
      cout << "done" << endl; 
      cout << myPlaylist.getPlaylistSize(); 
>>>>>>> 3368c7920501af25254266358da923b48ecf11d1
    }

    while(playlistInit && running){
        std::getline(std::cin, input);
        cmd = input.substr(0, input.find(" ")); 

        //add song
        if(cmd == "i"){
            myPlaylist.addSong(input.substr(2)); 
        }
        //play song 
        else if(cmd == "p"){
            myPlaylist.playSong(stoi(input.substr(1))); 
        }
        //erase song
        else if(cmd == "e"){
<<<<<<< HEAD
            myPlaylist.delSong(stoi(input.substr(1))); 
=======
          myPlaylist.delSong(stoi(input.substr(1))); 
>>>>>>> 3368c7920501af25254266358da923b48ecf11d1
        }
        //end program 
        else if(cmd == "done"){
            running = false; 
        }
        else{

        }
    }

}