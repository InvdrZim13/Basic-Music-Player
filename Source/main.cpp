#include "stdafx.h"  //needed for the Windows display
#include "globals.h"  //some global variables are included here
#include <cstdlib>	//standard c library
#include "mediaItem.h"  //the mediaItem class  (you need to write a class that extends this class)
#include "song.h"
#include <fstream>
#include <string>
using namespace std;

//declare global variables here (your song and playlist arrays)
ifstream file;
song songname[MAX_SONGS];
int songplaylist[MAX_PLAYLIST];

//as well as ints describing the current number of entries in each of these)
int number_of_songs = 0;
int counter = 0;

bool loadSongList(string filename)
{
	string artist[100];
	string name[100];
	string location[100];
	int a = 0;

	file.open(filename); // input string filename 
	if (file.is_open())
	{
		file >> number_of_songs; // number of songs.
		file.ignore(); // ignore the first line (number of songs = 33) from text file.
		while (file.good()) // gets next line
		{
			getline(file, artist[a]); //reads line by line.
			getline(file, name[a]);
			getline(file, location[a]);
			a++;
		}
		a--;
		for (int i = 0; i < number_of_songs; i++)
		{
			songname[i].setArtist(artist[i]); //sets artist
			songname[i].setTitle(name[i]);    //sets title
			songname[i].setLocation(location[i]); //sets location
		}

		return true;
	}
	else return false;
}

int getNumberOfSongsInSongList()
{
	return number_of_songs;
}

string getSongNameFromSongList(int songNum)
{
	return songname[songNum].getArtist() + " - " + songname[songNum].getTitle();
}

string getSongNameFromPlaylist(int playlistSpot)
{
	string songfile;  //song choice

	int songspot = songplaylist[playlistSpot];

	string artist = songname[songspot].getArtist(); // get artist from playlist
	string songtitle = songname[songspot].getTitle();

	int sizeofartist = artist.length();  // finds length of artist and title.
	int sizeofsong = songtitle.length();

	for (int i = 0; i < sizeofartist; i++)  //loads each character into array (artist)
		songfile.push_back(artist[i]);

	songfile.push_back(' ');  //adds space between artist and title.
	songfile.push_back('-');
	songfile.push_back(' ');

	for (int i = 0; i < sizeofsong; i++) // loads each character into array (title)
		songfile.push_back(songtitle[i]);

	return songfile;
}

void addSongToPlaylist(int songNum)
{
	songplaylist[counter] = songNum; // playlist songs is equal to the number of the song. points to location of song.
	counter = counter + 1; // adds song to playlist, keeps a counter. 
}

int getNumberOfSongsInPlaylist()
{
	return counter; // amount of sonds in playlist.
}

void removeSongFromPlaylist(int playlistSpot)
{
	int temp[MAX_PLAYLIST];
	int j = 0;

	for (int i = 0; i < MAX_PLAYLIST; i++)  // creates temp array, copies songplaylist
		temp[i] = songplaylist[i];

	for (int i = 0; i < MAX_PLAYLIST; i++) // erases songplaylist
		songplaylist[i] = -1;

	for (int i = 0; i < MAX_PLAYLIST; i++) // reprints array.
	{
		if (i != playlistSpot)
		{
			songplaylist[j] = temp[i];
			j++;
		}
	}

	counter--;  // keeps counter of playlist songs.
}

void clearPlaylist()
{
	for (int i = 0; i < MAX_PLAYLIST; i++)  // takes all playlist songs and sets them to -1. 
		songplaylist[i] = -1;
	counter = 0; //resets counter to zero.
}

void moveSongUpInPlaylist(int playlistSpot)
{ // flips the selected song with the song below.
	int counter2 = 0;
	int d = songplaylist[playlistSpot];
	int temp = songplaylist[playlistSpot - 1];

	songplaylist[playlistSpot] = temp; //flip the songs.
	songplaylist[playlistSpot - 1] = d;

}

void moveSongDownInPlaylist(int playlistSpot)
{ // same way as moving list up but in reversed.

	int d = songplaylist[playlistSpot];
	int temp = songplaylist[playlistSpot + 1];

	songplaylist[playlistSpot] = temp;
	songplaylist[playlistSpot + 1] = d;
}

void playSongFromPlaylist(int playlistSpot)
{
	songname[songplaylist[playlistSpot]].playMedia();
}

void pauseSongFromPlaylist(int playlistSpot)
{
	songname[songplaylist[playlistSpot]].pauseMedia();
}

void stopSongFromPlaylist(int playlistSpot)
{
	songname[songplaylist[playlistSpot]].stopMedia();
}
