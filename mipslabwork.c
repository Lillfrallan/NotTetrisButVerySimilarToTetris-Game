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
int timeoutcount = 0;
int prime = 1234567;
char textstring[] = "text, more text, and even more text!";


/* Interrupt Service Routine */
void user_isr( void ) {
  
  if(IFS(0) & 0x0080){
    IFSCLR(0) = 0x0080; //reset status flag 
    PORTE++;
    }

  if(IFS(0) & 0x0100){
    IFSCLR(0) = 0x0100; //reset status flag
    timeoutcount++;
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* ptrTrisE = (volatile int*) 0xbf886100;    // TRISEx sets input(1)/output(0)
  *ptrTrisE = 0x00;     // points to an address and sets LEDs to outputs
  TRISDSET = 0xfe0;     // sets all switches and buttons 2,3,4 to inputs
  TRISFSET = 0x2;       // set button 1 to input

  T2CON = 0x0;          // clears T2CON
  T2CONSET = 0x70;      // sets bits 6:4 to 1, thus prescale 1:256
  TMR2 = 0x0;           // clears timer
  PR2 = 31250;          // sets timer period

  IPCSET(2) = 0x0004;   // sets priority
  IEC(0) = 0x0100;      // enables interruption timer 2

  // Surprise assignment
  IECSET(0) = 0x0080;       // Enables interruption for sw1
  IPCSET(1) = 0x10000000;   // sets a priority

  // end surprise

  PORTE = 0x0;          // clear all LEDs

  T2CONSET = 0x8000;    // starts timer

  volatile int* IECdebug = (volatile int*) 0xbf881060;  // debug IEC
  volatile int* IPCdebug = (volatile int*) 0xbf8810b0;  // debug IPC
  //display_debug(IPCdebug);                            // debugger


  enable_interrupt(); // enables an interrupt
  return;
}