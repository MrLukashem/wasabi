
#include <iostream>
#include <alsa/asoundlib.h>

#define ALSA_PCM_NEW_HW_PARAMS_API

int main() {
    snd_pcm_t *handle;
    auto rc = snd_pcm_open(&handle, "default",
                    SND_PCM_STREAM_PLAYBACK, 0);
    //std::cout << "Hello wasabi!\n";
}