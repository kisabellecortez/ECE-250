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

    if((t_a == "Baby;Justin Bieber") || (title == "My Heart Will Go On") || (playlistS == currPlaylistS)){
        cout << "can not insert " + t_a << endl; 
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
            cout << "can not insert " + t_a << endl; 
        }
    } 
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

        currPlaylistS = currPlaylistS - 1; 

        cout << "success" << endl; 
    }
}