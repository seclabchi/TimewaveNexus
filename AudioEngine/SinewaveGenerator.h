#ifndef __SINEWAVE_GENERATOR_H__
#define __SINEWAVE_GENERATOR_H__

#include <stdint.h>

class SinewaveGenerator
{
	public:
		SinewaveGenerator(uint16_t frequency, uint16_t sample_rate);
		void init();
		void getBuffer(int16_t* buf, uint16_t len);
		virtual ~SinewaveGenerator();
	private:
		uint16_t m_frequency;
		uint16_t m_sample_rate;
		int16_t* m_audio_buf;
		int16_t* m_src_buf_pos;
		int16_t* m_dst_buf_pos;
		uint16_t m_src_buf_remaining;
		uint16_t m_dst_buf_remaining;
};

#endif // __SINEWAVE_GENERATOR_H__
