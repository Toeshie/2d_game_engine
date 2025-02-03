#pragma once
#include "Component.h"
#include <string>

class AudioComponent : public Component {
private:
    std::string sound_name_;
    float volume_ = 1.0f;
    bool is_looping_ = false;
    int channel_ = -1;

public:
    AudioComponent() = default;
    virtual ~AudioComponent() = default;

    void set_sound(const std::string& sound_name) { sound_name_ = sound_name; }
    void set_volume(float volume) { volume_ = volume; }
    void set_looping(bool loop) { is_looping_ = loop; }

    void play();
    void stop();
    void pause();
    void resume();

    virtual void on_destroyed() override;
};

