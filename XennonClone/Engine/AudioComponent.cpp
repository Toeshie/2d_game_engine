#include "AudioComponent.h"
#include "AudioManager.h"

void AudioComponent::play() {
    if (!sound_name_.empty()) {
        int loops = is_looping_ ? -1 : 0;
        AudioManager::get_instance()->play_sound(sound_name_, loops, channel_);
    }
}

void AudioComponent::stop() {
    if (channel_ != -1) {
        Mix_HaltChannel(channel_);
    }
}

void AudioComponent::pause() {
    if (channel_ != -1) {
        Mix_Pause(channel_);
    }
}

void AudioComponent::resume() {
    if (channel_ != -1) {
        Mix_Resume(channel_);
    }
}

void AudioComponent::on_destroyed() {
    stop();
}