
#define SPEW3D_DEBUG_OUTPUT
#define SPEW3D_IMPLEMENTATION
#include <spew3d.h>
#undef SPEW3D_IMPLEMENTATION
#include <math.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>


int main(int argc, const char **argv) {
    // WARNING, this is a specialized example using a decoder directly,
    // which doesn't easily allow you to play multiple sounds at once.
    // This is only a special example to show how to use decoders
    // directly, which isn't needed for the average game.
    // Check out this example instead: example_audio.c

    printf("Initializing Spew3D audio pipeline\n");
    s3d_audio_sink *sink = spew3d_audio_sink_CreateStereoOutput(48000);
    if (!sink) {
        fprintf(stderr, "Failed to create sink\n");
        return 1;
    }

    const char playfilename[] = "audiotest.mp3";

    // First, ensure we're in the right folder:
    int _exists = 0;
    if (!spew3d_fs_TargetExists(playfilename, &_exists) || !_exists) {
        fprintf(stderr, "You didn't run this in 'examples' folder, "
            "or there was an I/O error.\n");
        return 1;
    }

    // Then open decoder to play file:
    printf("Opening file to directly feed into output sink\n");
    s3d_audio_decoder *decoder = audiodecoder_NewFromFile(
        playfilename
    );
    if (!decoder || !spew3d_audio_sink_FeedFromDecoder(
            sink, decoder
            )) {
        fprintf(stderr, "Failed to set up decoded file.\n");
        return 1;
    }

    // Main event loop:
    printf("Entering main loop\n");
    int notquit = 1;
    while (notquit) {
        s3devent_UpdateMainThread();
        s3devent e = {0};
        while (s3devent_q_Pop(s3devent_GetMainQueue(), &e)) {
            if (e.type == S3DEV_WINDOW_USER_CLOSE_REQUEST ||
                    e.type == S3DEV_APP_QUIT_REQUEST) {
                notquit = 0;
                break;
            }
        }
    }

    printf("Shutting down\n");
    return 0;
}

