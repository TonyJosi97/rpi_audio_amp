
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
#include <sys/types.h>

typedef Uint8 OP_DBUF_T;

typedef struct __AUDIO_OUT {

    int                 sampling_Freq;
    Uint8               audio_Channel;
    Uint8               samples_Per_Frame;
    OP_DBUF_T          *ip_Data_Buffer_0; 
    OP_DBUF_T          *ip_Data_Buffer_1;
    pthread_mutex_t     buf_Lock;
    Uint8               ip_Data_Buffer_MUX;

} Audio_Out_t;

typedef enum {

    AUDIO_OUT_OK = 0,
    AUDIO_OUT_PROGRESS,
    AUDIO_OUT_FAIL,
    AUDIO_OUT_INVLD_ARG

} Audio_Out_Status_t;

typedef enum {

    AUDIO_OUT_BUFFER_0,
    AUDIO_OUT_BUFFER_1,
    AUDIO_OUT_BUFFER_2

} Audio_Out_Buffer_ID_t;

Audio_Out_Status_t audio_Out_Init(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Start_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Stop_Thread(Audio_Out_t *);
Audio_Out_Status_t audio_Out_Close(Audio_Out_t *);
