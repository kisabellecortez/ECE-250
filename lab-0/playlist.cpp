#include "playlist.h"
#include <iostream>

using namespace std; 

// implement classes' member functions here...

int Playlist::getPlaylistSize(){
    return playlistS; 
}; 

int Playlist::getCurrSize(){
    return currPlaylistS; 
}; 

void Playlist::addSong(string t_a){
    string title = t_a.substr(0, t_a.find(';')); 

    if((t_a == "Baby;Justin Beiber") || (title == "My Heart Will Go On") || (playlistS == currPlaylistS)){
        cout << "cannot insert " + t_a << endl; 
    } 
    else{
        bool songExists = false; 

        for(int i = 0; i < currPlaylistS; i++){
            if(t_a == playlist[i]){
                songExists = true; 
            }
        }

        if(!songExists){
            playlist[currPlaylistS] = t_a;
            currPlaylistS = currPlaylistS + 1; 

            cout << "success" << endl;
        }
        else{
            cout << "cannot insert " + t_a << endl; 
        }
    }
<<<<<<< HEAD
=======

  cout << playlist; 
>>>>>>> 3368c7920501af25254266358da923b48ecf11d1
}; 

void Playlist::playSong(int n){
    if(n >= currPlaylistS || currPlaylistS == 0){
        cout << "can not play " << n << endl; 
    }
    else{
        cout << "played "<< n << " " << playlist[n] << endl; 
    }
}; 

void Playlist::delSong(int n){
    if((n >= currPlaylistS) || (currPlaylistS == 0)){
<<<<<<< HEAD
        cout << "can not erase " << n << endl; 
    }
    else{
        if(currPlaylistS == 1){
            playlist[0] = ""; 
        }
        else{
            for(int i = n; i < currPlaylistS - 1; i++){
                playlist[i] = playlist[i + 1]; 
            }
        }
=======
        cout << "can not erase "; 
      cout << n << endl; 
    }
    else{
      if(currPlaylistS == 1){
        playlist[0] = ""; 
      }
      else{
        for(int i = n; i < currPlaylistS - 1; i++){
            playlist[i] = playlist[i + 1]; 
        }
      }
>>>>>>> 3368c7920501af25254266358da923b48ecf11d1

        currPlaylistS = currPlaylistS - 1; 

        cout << "success" << endl; 
    }
}