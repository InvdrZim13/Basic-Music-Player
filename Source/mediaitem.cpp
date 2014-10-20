#include "stdafx.h"
#include "mediaItem.h"
#include <iostream>

mediaItem::mediaItem()
{
	location = "";
	playing = false;
	opened = false;
}
mediaItem::~mediaItem()
{

}

void mediaItem::setLocation(string inLocation)
{
	location = inLocation;
}

string mediaItem::getLocation()
{
	return location;
}

//The following functions interface with the windows mmc library to manage the media files being played.  Do NOT edit this!
//Many of the concepts used below (pointers, dynamic allocation of memory, etc) you may not be familiar with.  Do not concern
//yourself with them, suffice to say that they allow for the wav files to be opened and played.
void mediaItem::playMedia()
{
	if(!opened)
	{
		stopMedia();
		string commandString = "open " + location + " type waveaudio alias MediaItem";
		int len;
		int slength = (int)commandString.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, commandString.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, commandString.c_str(), slength, buf, len);
		wstring command(buf);
		delete[] buf;

		mciSendString((LPCWSTR)command.c_str(), NULL, 0, 0);
		opened = true;
	}
	wchar_t* command2 = L"play MediaItem";
	mciSendString((LPCWSTR)command2, NULL, 0, 0);
	playing = true;
}

void mediaItem::pauseMedia()
{
	if(playing)
	{
		wchar_t* command2 = L"pause MediaItem";
		mciSendString((LPCWSTR)command2, NULL, 0, 0);
		playing = false;
	}
}

void mediaItem::stopMedia()
{
	if(opened)
	{
		wchar_t* command2 = L"close MediaItem";
		mciSendString((LPCWSTR)command2, NULL, 0, 0);
		opened = false;
	}
}
