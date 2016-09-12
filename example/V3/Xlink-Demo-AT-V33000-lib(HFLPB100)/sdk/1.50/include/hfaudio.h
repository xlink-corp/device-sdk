


/* hfaudio.h
 *
 * Copyright (C) 2013-2020 ShangHai High-flying Electronics Technology Co.,Ltd.
 *				  	All rights reserved.
 *
 * This file is part of HSF.
 *
 *
 */


#ifndef _HF_AUDIO_H__H_
#define _HF_AUDIO_H__H_

int hfaudio_enable(void);

void hfaudio_disable(void);

int hfaudio_pcm_play_init(uint32_t sample_rate,int channels);

int hfaudio_pcm_play(uint32_t start_addr,uint32_t length);


#endif



