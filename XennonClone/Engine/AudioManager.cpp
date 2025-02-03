#include "AudioManager.h"


AudioManager* AudioManager::instance_ = nullptr;

AudioManager::AudioManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        //Error
    }
}

AudioManager::~AudioManager() {
    clean();
}

void AudioManager::initialize() {
    if (!instance_) {
        instance_ = new AudioManager();
    }
}

void AudioManager::destroy() {
    if (instance_) {
        delete instance_;
        instance_ = nullptr;
    }
}

AudioManager* AudioManager::get_instance() {
    return instance_;
}

bool AudioManager::load_music(const std::string& path, const std::string& name) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        //error
        return false;
    }
    music_[name] = music;
    return true;
}

void AudioManager::play_music(const std::string& name, int loops) {
    auto it = music_.find(name);
    if (it != music_.end()) {
        Mix_PlayMusic(it->second, loops);
    }
}

bool AudioManager::load_sound(const std::string& path, const std::string& name) {
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound) {
        //error
        return false;
    }
    sound_effects_[name] = sound;
    return true;
}

void AudioManager::play_sound(const std::string& name, int loops, int channel) {
    auto it = sound_effects_.find(name);
    if (it != sound_effects_.end()) {
        Mix_PlayChannel(channel, it->second, loops);
    }
}

void AudioManager::clean() {
    for (auto& music : music_) {
        Mix_FreeMusic(music.second);
    }
    music_.clear();

    for (auto& sound : sound_effects_) {
        Mix_FreeChunk(sound.second);
    }
    sound_effects_.clear();

    Mix_CloseAudio();
}

// Music functions
void AudioManager::stop_music() {
    Mix_HaltMusic();
}

void AudioManager::pause_music() {
    Mix_PauseMusic();
}

void AudioManager::resume_music() {
    Mix_ResumeMusic();
}

// Volume control
void AudioManager::set_master_volume(float volume) {
    master_volume_ = volume;
    set_music_volume(music_volume_); // Update both music and SFX with new master volume
    set_sfx_volume(sfx_volume_);
}

void AudioManager::set_music_volume(float volume) {
    music_volume_ = volume;
    Mix_VolumeMusic(static_cast<int>(music_volume_ * master_volume_ * MIX_MAX_VOLUME));
}

void AudioManager::set_sfx_volume(float volume) {
    sfx_volume_ = volume;
    Mix_Volume(-1, static_cast<int>(sfx_volume_ * master_volume_ * MIX_MAX_VOLUME)); // -1 sets volume for all channels
}