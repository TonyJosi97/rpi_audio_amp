
/** 
 *  @file   audio_Output.c
 *  @brief  Source file for API to output audio via the PI audio card
 *
 *  This contains the Source file for utility functions to 
 *  output audio via the PI audio card
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <math.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "../inc/audio_Output.h"

void audio_Out_Callback(void* data, Uint8 *stream, int len);

typedef struct __AUDIO_OP_INTERNAL {

    uint8_t                 stop_Thread;
    pthread_mutex_t        *lock_Ptr;
    SDL_AudioSpec          *ao_Spec_ptr;

} Audio_OP_Internal_t;


Audio_Out_Status_t audio_Out_Init(Audio_Out_t *ao_user_Obj) {

    SDL_AudioSpec *__audio_Spec_Ptr = malloc(sizeof(SDL_AudioSpec));
    if(__audio_Spec_Ptr == NULL) goto __Free_mem_N_Return;

    __Free_mem_N_Return:
        

}

Audio_Out_Status_t audio_Out_Start_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Stop_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Close(Audio_Out_t *);

void audio_Out_Callback(void* data, Uint8 *stream, int len) {

} 
