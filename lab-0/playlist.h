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
<<<<<<< HEAD
            playlistS = N; 
=======
          playlistS = N; 
>>>>>>> 3368c7920501af25254266358da923b48ecf11d1
            currPlaylistS = 0; 
            playlist = new string[N]; 
        }
}; 