/*****************************************************************************
 *   timer.h:  Header file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __TIMER_H 
#define __TIMER_H

#define INTERVAL_10MS	149999			/* 10mSec = 150.000-1 counts */

extern DWORD init_timer  ( BYTE timer_num );
extern void enable_timer ( BYTE timer_num );
extern void disable_timer( BYTE timer_num );
extern void reset_timer  ( BYTE timer_num );

#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
