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

int timeoutcount = 0; //global bariable for timeoutcount
volatile int *trisE;
volatile int *portE;
//assignment3
int prime = 1234567;

/* Interrupt Service Routine */
void user_isr( void ) { //executed when the Timer 2 interrupt occurs.
 if(IFS(0) & 0x0100)
 { // Check if time out event
    timeoutcount++; //f
    if(timeoutcount==10)
    {
        time2string( textstring, mytime );
        display_string( 3, textstring );
        display_update();
        tick( &mytime );
        timeoutcount=0;
    }
    IFSCLR(0) = 0x100; // Clear the flag
 }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  //volatile int* TRISE = (volatile int*)0xbf886100
  //c
  trisE = (volatile int*) 0xbf886100; // Address of TRISE register
  *trisE = *trisE & 0xffffff00; // LSB 0 means output PORTE

  //d
  portE = (volatile int*) 0xbf886110; // Address of PORTE register
  *portE = 0x00000000; // allt släckt

  // e)
  TRISD = TRISD | 0x0fe0; // OR to keep values at 11-5 bits 
  //0000 1111 1110 0000 bit 5 to 11 are input (1) och resten unchanged
  


  //assignment 2a
  T2CON= 0x00; // ON bit 0 to stop the clock
  T2CONSET= 0x70; // 0111 000 indikerar prescaling 1:256 så biytar 4-6 är prescaling bits
  TMR2=0x0; //start counting from 0 when enabled
  PR2= ((80000000/256)/10);
  T2CONSET= 0x8000;// start the time bu set ON to 1   1000


  IEC(0) = 1 << 8;//IECSET(0) = 0x100;//enable interrupt the 8th bit thats timer 2 0000 0001 0000 0000
  // Interrupt priority. Bit 4-2 is T2IP.
  // Setting priority 7 and sub-priority 3.
  // bit 4-2: 0111 = 7
  // bit 1-0: 11 = 3
  // IPC2: 000111 11 = 0x1F
  IPCSET(2) = 0x1F; //IPC(2) = 7 << 2;//ipc prioterar vilken interupts som är viktigast typ 
  // priotity är bit 4-2 0001 1100 and subpriority är bit 1-0 11
  // 0001 1111
  enable_interrupts(); //  IECSET= 0x1F; enables alla interrupt
return;
}


/* This function is called repetitively from the main program */

void labwork( void ) {
 prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();
}




/*
void labwork( void )
{
  int switches = getsw();
	int button = getbtns();

  if(button & 1){
    mytime = mytime & 0xff0f;
    mytime = (switches << 4) | mytime;
  }
  if(button & 2){
    mytime = mytime & 0xf0ff;
    mytime = (switches << 8) | mytime;
  }
  if(button & 4){
    mytime = mytime & 0x0fff;
    mytime = (switches << 12) | mytime;
  }


  if(IFS(0) & 0x100){ //if flag is 1 representet by the 8th bit
    timeoutcount++;
    IFSCLR(0) = 0x100; //clear the flag
  }

  if (timeoutcount==10){ //every 10th interrupt
    delay( 1000 );
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    display_image(96, icon);
    timeoutcount =0; //reset
  }
}*/
