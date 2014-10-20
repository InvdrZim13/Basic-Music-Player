#include "stdafx.h"
#include "song.h"
#include <string>


song::song() :mediaItem()	 //default constructor
{

}
string song::getArtist() // return artist name
{
	return artist;
}
string song::getTitle() // return song title
{
	return title;
}
void song::setArtist(string artistIn) // set the artistname
{
	artist = artistIn;
}
void song::setTitle(string titleIn) //set the song title
{
	title = titleIn;
}
