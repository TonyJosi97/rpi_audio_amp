#include "../inc/audio_Output.h"

#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define S_FREQ      44100
#define SAMPLES     8192
#define VOLUME      127.0

void fill_Buffer(Audio_Out_t *_Obj);

int main(int argc, char* argv[]) {

    Audio_Out_t main_Obj;
    main_Obj.sampling_Freq = S_FREQ;
    main_Obj.audio_Channel = 1;
    main_Obj.samples_Per_Frame = SAMPLES;
    main_Obj.ip_Data_Buffer_0 = (OP_DBUF_T *) malloc(sizeof(OP_DBUF_T) * SAMPLES);
    main_Obj.ip_Data_Buffer_1 = (OP_DBUF_T *) malloc(sizeof(OP_DBUF_T) * SAMPLES);
    
    if(audio_Out_Init(&main_Obj) != AUDIO_OUT_OK) {
        printf("Init Failed\n");
    }

    fill_Buffer(&main_Obj);
    audio_Out_Start_Thread();

    while (1) {
        sleep(1);
        fill_Buffer(&main_Obj);
    }

    return 0;

}

void fill_Buffer(Audio_Out_t *_Obj) {

    OP_DBUF_T *temp_ptr = NULL;

    pthread_mutex_lock(&(_Obj->buf_Lock));
    
    if(_Obj->ip_Data_Buffer_MUX == AUDIO_OUT_BUFFER_0) {
        temp_ptr = _Obj->ip_Data_Buffer_0; 
    } else if (_Obj->ip_Data_Buffer_MUX == AUDIO_OUT_BUFFER_1) {
        temp_ptr = _Obj->ip_Data_Buffer_1;
    }

    for(int i = 0; i < _Obj->samples_Per_Frame; ++i) {
        temp_ptr[i] = (OP_DBUF_T) (VOLUME * sinf(2 * M_PI * 50 / S_FREQ * i)) + 127;
    }   
    
    pthread_mutex_unlock(&(_Obj->buf_Lock)); 
    
}
