/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  //volatile int* TRISE = (volatile int*)0xbf886100
  //c
  trisE = (volatile int*) 0xbf886100; // Address of TRISE register
  *trisE = *trisE & 0xffffff00; // LSB 0 means output PORTE

  //d
  port_E = (volatile int*) 0xbf886110; // Address of PORTE register
  *port_E = 0x00000000; // allt släckt

  // e)
  TRISD = TRISD | 0x0fe0; // OR to keep values at 11-5 bits 
  //0000 1111 1110 0000 bit 5 to 11 are input (1) och resten unchanged
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int switches = getsw();
	int buttons = getbtns(); //0000 0000 1110 0000===0000 0000 0000 0111

  // Button 2 (001)
  if(buttons & 1){
    mytime = mytime & 0xff0f;
    mytime = (switches << 4) | mytime;
  }
  // Button 3 (010)
  if(buttons & 2){
    mytime = mytime & 0xf0ff; //0X:00
    mytime = (switches << 8) | mytime;
  }
  // Button 4 (100)
  if(buttons & 4){
    mytime = mytime & 0x0fff;
    mytime = (switches << 12) | mytime;
  }

  //d
  volatile int mytime=0x0000;
  *PORTE= mytime & 0xFF;

  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
}
