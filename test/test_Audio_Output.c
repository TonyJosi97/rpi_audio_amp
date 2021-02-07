
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>

#define S_FREQ      44100
#define SAMPLES     8192
#define VOLUME      127.0
#define MI_SEC      1


float freq = 500;

void audio_Out_Callback(void* data, Uint8 *stream, int len) {

    //printf("Len: %d\n", len);

    //pthread_mutex_lock(&(__gs_Audio_Obj.ao_Out_Obj_ptr->buf_Lock));
    /*
    if(__gs_Audio_Obj.ao_Out_Obj_ptr->ip_Data_Buffer_MUX == AUDIO_OUT_BUFFER_0) {
        __gs_Audio_Obj.ao_Out_Obj_ptr->ip_Data_Buffer_MUX == AUDIO_OUT_BUFFER_1;
        temp_buf_ptr = __gs_Audio_Obj.ao_Out_Obj_ptr->ip_Data_Buffer_0;
    } else {
        __gs_Audio_Obj.ao_Out_Obj_ptr->ip_Data_Buffer_MUX == AUDIO_OUT_BUFFER_0;
        temp_buf_ptr = __gs_Audio_Obj.ao_Out_Obj_ptr->ip_Data_Buffer_1;
    } 
    */
   static double prev_val = 0;
   static double step =  2 * M_PI * 500 / S_FREQ;

    for (int i = 0; i < len; ++i) {
        //if(temp_buf_ptr[i] == 0)
        //printf("%d\n", temp_buf_ptr[i]);
        stream[i] = (Uint8) (VOLUME * sin(prev_val)) + 127;
        prev_val += step;
		//printf("%d\n", stream[i]);

    }

    printf("%f\n", prev_val);
    //memcpy(stream, temp_buf_ptr, len);
    //pthread_mutex_unlock(&(__gs_Audio_Obj.ao_Out_Obj_ptr->buf_Lock));
    
} 

int main(int argc, char* argv[]) {

    SDL_AudioSpec __audio_Spec_Ptr;

    __audio_Spec_Ptr.freq = S_FREQ;
    __audio_Spec_Ptr.format = AUDIO_U8;
    __audio_Spec_Ptr.channels = 1;
    __audio_Spec_Ptr.samples = SAMPLES;
    __audio_Spec_Ptr.callback = (*audio_Out_Callback);
    __audio_Spec_Ptr.userdata = NULL;

    if(SDL_OpenAudio(&__audio_Spec_Ptr, NULL) != 0) {
        return -1; 
    }



    struct timespec ts;
    ts.tv_sec = MI_SEC / 1000;
    ts.tv_nsec = (MI_SEC % 1000) * 1000000;

    SDL_PauseAudio(0); 

    sleep(5);

	/* Then turn it off again */
	SDL_PauseAudio(1);

	/* Close audio channel */
	SDL_CloseAudio();

    return 0;

}

