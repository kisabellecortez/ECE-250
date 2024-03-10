#include <iostream>
#include <string>
#include <array>

using namespace std; 

// define your classes here...

class Playlist{
    private: 
        int playlistS; 
        int currPlaylistS;  
        string *playlist; 

    public: 
        int getPlaylistSize();
        int getCurrSize();  
        void addSong(std::string t_a); 
        void playSong(int n); 
        void delSong(int n); 

        Playlist(){ 

        }
        Playlist(int N){
          playlistS = N; 
            currPlaylistS = 0; 
            playlist = new string[N]; 
        }
};