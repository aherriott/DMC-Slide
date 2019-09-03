#include "APA102.h"
#include "mbed.h"

#define START_FRAME_LENGTH			4
#define START_FRAME					0x00, 0x00, 0x00, 0x00
#define END_FRAME_BYTES(num_led) 	(num_led/16 + 1)

APA102::APA102(PinName mosi,PinName miso,PinName sclk,int rate, int length)
        : _spi(mosi, miso, sclk), _strip(length),
		  _start_frame(NULL), _end_frame(NULL), _end_frame_length(END_FRAME_BYTES(length))
{
	// Setup the spi for 8 bit data, high steady state clock,
	// second edge capture, with a 1MHz clock rate
	_spi.format(8,3);
	_spi.frequency(rate);


	_start_frame = new char[START_FRAME_LENGTH];
	for(int i=0; i<START_FRAME_LENGTH; i++)
	{
		_start_frame[i] = 0x00;
	}
	_end_frame = new char[_end_frame_length];
	for(int i=0; i<_end_frame_length; i++)
	{
		_end_frame[i] = 0x00;
	}
}
        
void APA102::SetLED(LED led, int loc)
{
	MBED_ASSERT(loc >= 0);
	MBED_ASSERT(loc < _strip.size());

	led.brightness |= 0b11100000; // brightness is 5 bits. First 3 bits are all 1.
	_strip[loc] = led;
}

void APA102::Show()
{   
	// Start frame (0x00 *4)
	_spi.write(_start_frame, START_FRAME_LENGTH, NULL, 0);

    _spi.write((const char*)&_strip[0], _strip.size()*sizeof(LED), NULL, 0);

    // Reset frame (0x00 *4)
	_spi.write(_start_frame, START_FRAME_LENGTH, NULL, 0);

    // End frame (0x00 * n/16)
    _spi.write(_end_frame, _end_frame_length, NULL, 0);
}
