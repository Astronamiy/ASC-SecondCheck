#ifndef __ENCODER_H
#define __ENCODER_H

#define ENCODER_PRESSED1 							1
#define ENCODER_PRESSED2 							2
#define ENCODER_UNPRESSED 							0

#define Encoder_Turn1							 	0x01
#define Encoder_Turn2							 	0x02

void Encoder_Init(void);
int16_t Encoder_Get(void);





#endif
