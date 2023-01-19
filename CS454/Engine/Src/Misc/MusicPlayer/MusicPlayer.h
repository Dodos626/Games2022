#pragma once
#ifndef MUSIC_PLAYER_INCLUDE
#define MUSIC_PLAYER_INCLUDE

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>


//.wav, .flac, .ogg, .it, .mod, .s3m, .xm.
class MusicPlayer {
private:
	std::vector<ALLEGRO_SAMPLE*> samples;
	int index_playing;
	float volume;
public:
	MusicPlayer();

	void Play(int index);
	void PlayRandom(void);

	void Stop();

	
	
};

#endif