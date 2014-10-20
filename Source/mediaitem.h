#ifndef MEDIAITEM
#define MEDIAITEM

#include <string>
using namespace std;

//This is a general class for playing media files.  You should write a class that extends this class
//(make a child class with this as its parent).  Your class should extend this class with the ability
//to set and get the artist and title for a song.

class mediaItem
{
public:
	mediaItem();	//constructor
	~mediaItem();	//destructor

	string getLocation();			//returns the location of the media file on disk
	void setLocation(string inLocation);	//sets the location of the media file on disk
	
	void playMedia();	//plays the media file
	void pauseMedia();	//pauses the media file
	void stopMedia();	//stops the media file

private:
	string location;	//the location of the media file on disk	
	bool playing;		//boolean indicating if the file is currently playing
	bool opened;		//boolean indicating if the file is currently opened
};

#endif
