/*
 * main.cpp
 *
 *  Created on: Jun 4, 2019
 *      Author: alexh
 */

#include "APA102.h"
#include "HTML_color.h"

#define STRIP_LENGTH (5*60)
#define SPI_RATE 1000000

APA102 mystrip(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_RATE, STRIP_LENGTH);


int rainbow_strip[STRIP_LENGTH];

void move(void){
	int i = 0;
	static int idx = 0;
	idx++;
    while(i < STRIP_LENGTH)
    {
    	LED color;
    	int color_idx = (idx + i) % 60;

		color.brightness = 1;
		color.red = 0;
		color.green = 0;
		color.blue = 0;
		if(color_idx < 10)
		{
			color.red = 255;
			color.green = color_idx*255/60;
		}
		else if(color_idx < 20)
		{
			color.red = 255 - color_idx*255/60;
			color.green = 255;
		}
		else if(color_idx < 30)
		{
			color.blue = color_idx*255/60;
			color.green = 255;
		}
		else if(color_idx < 40)
		{
			color.green = 255 - color_idx*255/60;
			color.blue = 255;
		}
		else if(color_idx < 50)
		{
			color.red = color_idx*255/60;
			color.blue = 255;
		}
		else
		{
			color.blue = 255 - color_idx*255/60;
			color.red = 255;
		}

    	mystrip.SetLED(color, i);
    	i++;
    }
    idx = idx % 60;
}

int main()
{
    while(1)
	{
		move();
		mystrip.Show();
		wait_ms(100);
	}
}

