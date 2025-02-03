#pragma once
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

class AudioManager {
private:
    static AudioManager* instance_;
    std::unordered_map<std::string, Mix_Music*> music_;
    std::unordered_map<std::string, Mix_Chunk*> sound_effects_;
    
    float master_volume_ = 1.0f;
    float music_volume_ = 1.0f;
    float sfx_volume_ = 1.0f;

public:
    static AudioManager* get_instance();
    static void initialize();
    static void destroy();

    // Music functions
    bool load_music(const std::string& path, const std::string& name);
    void play_music(const std::string& name, int loops = -1);
    void stop_music();
    void pause_music();
    void resume_music();

    // Sound effect functions
    bool load_sound(const std::string& path, const std::string& name);
    void play_sound(const std::string& name, int loops = 0, int channel = -1);

    // Volume control
    void set_master_volume(float volume);
    void set_music_volume(float volume);
    void set_sfx_volume(float volume);

private:
    AudioManager();
    ~AudioManager();
    void clean();
};
