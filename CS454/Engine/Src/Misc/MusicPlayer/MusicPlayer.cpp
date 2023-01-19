#include "MusicPlayer.h"

using json = nlohmann::json;


MusicPlayer::MusicPlayer() {
	std::ifstream fin("Engine/Configs/MusicConfig.json");
	json data = json::parse(fin);
	std::cout << data << std::endl;

	std::string sample = data["songs_path"]["palace_theme"];
	
	this->samples.push_back(al_load_sample(sample.c_str()));

	this->volume = data["volume"];

	this->index_playing = -1;

}

void MusicPlayer::Play(int index) {
	if (index > this->samples.size() || index < 0) {
			std::cerr << "Invalid index" << std::endl;
			exit(EXIT_FAILURE);
	}
	
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
