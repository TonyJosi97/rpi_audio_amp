
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
#include <assert.h>

#include "../inc/audio_Output.h"

#define __NULL_POINTER_CHECK(ptr)   assert(ptr != NULL)

void audio_Out_Callback(void* data, Uint8 *stream, int len);

typedef struct __AUDIO_OP_INTERNAL {

    uint8_t                 stop_Thread;
    Audio_Out_t            *ao_Out_Obj_ptr;

} Audio_OP_Internal_t;

static Audio_OP_Internal_t __gs_Audio_Obj;

Audio_Out_Status_t audio_Out_Init(Audio_Out_t *ao_user_Obj) {

    __NULL_POINTER_CHECK(ao_user_Obj);

    SDL_AudioSpec *__audio_Spec_Ptr = malloc(sizeof(SDL_AudioSpec));
    if(__audio_Spec_Ptr == NULL) goto __Free_mem_N_Return;

    __audio_Spec_Ptr->freq = ao_user_Obj->sampling_Freq;
    __audio_Spec_Ptr->format = AUDIO_U8;
    __audio_Spec_Ptr->samples = ao_user_Obj->samples_Per_Frame;
    __audio_Spec_Ptr->callback = audio_Out_Callback;
    __audio_Spec_Ptr->userdata = ao_user_Obj;

    if(SDL_OpenAudio(__audio_Spec_Ptr, NULL) != 0) 
        return AUDIO_OUT_FAIL; 

    __gs_Audio_Obj.stop_Thread = 1;
    __gs_Audio_Obj.ao_Out_Obj_ptr = ao_user_Obj;

    return AUDIO_OUT_OK;

__Free_mem_N_Return:
    free(__audio_Spec_Ptr);
    return AUDIO_OUT_FAIL;

}

Audio_Out_Status_t audio_Out_Start_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Stop_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Close(Audio_Out_t *);

void audio_Out_Callback(void* data, Uint8 *stream, int len) {

} 
