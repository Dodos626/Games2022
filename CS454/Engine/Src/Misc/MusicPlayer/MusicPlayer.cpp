#include "MusicPlayer.h"

using json = nlohmann::json;


MusicPlayer::MusicPlayer() {
	std::ifstream fin("Engine/Configs/MusicConfig.json");
	json data = json::parse(fin);

	std::string sample = data["songs_path"]["main_theme"];
	std::string sample2 = data["songs_path"]["palace_theme"];
	
	
	this->samples.push_back(al_load_sample(sample.c_str()));
	this->samples.push_back(al_load_sample(sample2.c_str()));
	

	this->volume = data["volume"];

	this->index_playing = -1;
	fin.close();

}

void MusicPlayer::Play(int index) {
	if (index > this->samples.size() || index < 0) {
			std::cerr << "Invalid index" << std::endl;
			exit(EXIT_FAILURE);
	}
	this->Stop();
	this->index_playing = index;
	al_play_sample(this->samples[index], this->volume, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
	
}
void MusicPlayer::PlayRandom(void) {
	return;
}
void MusicPlayer::Stop() {
	if (this->index_playing == -1) {
		return;
	}
	this->index_playing = -1;
	al_stop_samples();
	
}
