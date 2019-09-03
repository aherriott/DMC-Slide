#ifndef MBED_APA102_H

#define MBED_PING_H
 
#include "mbed.h"
#include <vector>

typedef struct __attribute__((__packed__)){
	unsigned char brightness;
	unsigned char blue;
	unsigned char green;
	unsigned char red;
} LED;

/** Create an APA102 Object 
    */ 
 class APA102{
  public:
/** Create an APA102 object connected to the specified mosi,miso,sclk pins
    *
    * @param mosi : SPI Master Out Slave In pin
    * @param miso : SPI Master In Slave Out pin (ignored)
    * @param sclk : SPI Clock
    * @param rate : SPI Rate
    */
     APA102(PinName mosi,PinName miso,PinName sclk,int rate, int length);
       
/** Set the Buffer
     *
     * @param buffer[] : a buffer of unsigned integers (4 bytes)
     */
     void SetLED(LED led, int loc);
     
/** Repaint the Strip
     *
     * @param none
     */
     void Show();
     
  protected:
    SPI _spi;
  private: 
    std::vector<LED> _strip;
    char *_start_frame;
    char *_end_frame;
    const int _end_frame_length;
 };
 
#endif
