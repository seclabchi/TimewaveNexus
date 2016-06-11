#include "SinewaveGenerator.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const double PI = 3.1415926535897;

SinewaveGenerator::SinewaveGenerator(uint16_t frequency = 1000, uint16_t sample_rate = 44100)
{
	m_frequency = frequency;
	m_sample_rate = sample_rate;
	m_audio_buf = NULL;
}

void SinewaveGenerator::init()
{
	//the buffer is initialized to hold one second
	m_audio_buf = new int16_t[m_sample_rate];
	m_src_buf_pos = m_audio_buf;
	m_src_buf_remaining = m_sample_rate;
	
	double samprate = (double)m_sample_rate;
	
	for(uint16_t i = 0; i <  m_sample_rate; i++)
	{
		m_audio_buf[i] = 32767.0 * sin(2.0*PI*(double)m_frequency*((double)i/samprate));
		printf("%d ", m_audio_buf[i]);
	}
	
	fflush(stdout);
	
	return;
}

SinewaveGenerator::~SinewaveGenerator()
{
	if(NULL != m_audio_buf)
	{
		delete[] m_audio_buf;
	}
}

void SinewaveGenerator::getBuffer(int16_t* buf, uint16_t len)
{
	m_dst_buf_pos = buf;
	m_dst_buf_remaining = len;
	
	if(len <= m_src_buf_remaining)
	{
		memcpy(m_dst_buf_pos, m_src_buf_pos, len * sizeof(uint16_t));
		m_src_buf_pos += len;
		m_src_buf_remaining -= len;
		if(0 == m_src_buf_remaining)
		{
			m_src_buf_pos = m_audio_buf;
			m_src_buf_remaining = m_sample_rate;
		}
		printf(".");
		fflush(stdout);
	}
	else
	{
		//copy the samples up to the end of the buffer first
		memcpy(m_dst_buf_pos, m_src_buf_pos, m_src_buf_remaining * sizeof(int16_t));
		m_dst_buf_pos += m_src_buf_remaining;
		m_dst_buf_remaining -= m_src_buf_remaining;
		printf("P");
		fflush(stdout);

		//reset the buffer pointer and size remaining
		m_src_buf_pos = m_audio_buf;
		m_src_buf_remaining = m_sample_rate;
		//copy the remainder of the requested data
		memcpy(m_dst_buf_pos, m_src_buf_pos, m_dst_buf_remaining * sizeof(int16_t));
		printf("R");
		fflush(stdout);
	}
}

