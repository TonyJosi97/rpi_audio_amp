
/** 
 *  @file   audio_Output.h
 *  @brief  Header file for API to output audio via the PI audio card
 *
 *  This contains the Header file for utility functions to 
 *  output audio via the PI audio card
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include <stdint.h>
#include <pthread.h>

typedef uint8_t U8;

typedef struct __AUDIO_OUT {

    int                 sampling_Freq;
    uint8_t             audio_Channel;
    uint8_t             samples_Per_Frame;
    uint16_t           *ip_Data_Buffer_1; 
    uint16_t           *ip_Data_Buffer_2;
    pthread_mutex_t     buf_Lock;

} Audio_Out_t;

typedef enum {

    AUDIO_OUT_OK = 0,
    AUDIO_OUT_PROGRESS,
    AUDIO_OUT_FAIL,
    AUDIO_OUT_INVLD_ARG

} Audio_Out_Status_t;

Audio_Out_Status_t audio_Out_Init(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Start_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Stop_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Close(Audio_Out_t *);
