/*****************************************************************************
 *   type.h:  Type definition Header file for Philips LPC214x Family 
 *   Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __TYPE_H__
#define __TYPE_H__

typedef unsigned char		U8;	
typedef unsigned short int	U16;	
typedef unsigned int		U32;	

typedef signed char		S8;	
typedef signed short int	S16;
typedef signed int		S32;

typedef float                   f32;

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#endif  /* __TYPE_H__ */
