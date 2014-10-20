#ifndef SONG
#define SONG

#include <string>
#include "mediaItem.h"

class song :public mediaItem{
public:
	song(); //default constructor
	string getArtist();// return artist name
	string getTitle(); // return song title
	void setArtist(string artistIn); // set the artistname
	void setTitle(string titleIn); //set the song title

private:
	string artist;
	string title;
};

#endif
