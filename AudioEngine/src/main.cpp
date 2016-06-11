#include <stdio.h>
#include <stdint.h>
#include <alsa/asoundlib.h>

#include "SinewaveGenerator.h"


static char *device = "default";                        /* playback device */
snd_output_t *output = NULL;
uint16_t bufSize = 16*1024;
                         /* some random data */


int main(void)
{
	SinewaveGenerator* sine = new SinewaveGenerator(400, 48000);
	sine->init();
	int16_t buffer[bufSize]; 
        int err;
        unsigned int i;
        snd_pcm_t *handle;
        snd_pcm_sframes_t frames;
		
		int result = 0;
		
		void** hints = 0;
		
		snd_device_name_hint(-1, "pcm", &hints);
		
		void* hint = 0;
		int hintNum = 0;
		char* retVal = 0;
		
		do
		{
			hint = hints[hintNum];
			if(NULL != hint)
			{
				retVal = snd_device_name_get_hint(hint, "NAME");
				printf("%s\n", retVal);
				hintNum++;
			}
		} while(NULL != hint);
		
		
        if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
        if ((err = snd_pcm_set_params(handle,
                                      SND_PCM_FORMAT_S16,
                                      SND_PCM_ACCESS_RW_INTERLEAVED,
                                      1,
                                      48000,
                                      1,
                                      50000)) < 0) {   /* 50ms */
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
        }
		
		
        while(1) {
				sine->getBuffer(buffer, bufSize);

                frames = snd_pcm_writei(handle, buffer, sizeof(buffer)/2);
                if (frames < 0)
                        frames = snd_pcm_recover(handle, frames, 0);
                if (frames < 0) {
                        printf("snd_pcm_writei failed: %s\n", snd_strerror(frames));
                        break;
                }
                if (frames > 0 && frames < (long)sizeof(buffer)/2)
                        printf("Short write (expected %li, wrote %li)\n", (long)sizeof(buffer)/2, frames);
        }
        snd_pcm_close(handle);
        return 0;
}
