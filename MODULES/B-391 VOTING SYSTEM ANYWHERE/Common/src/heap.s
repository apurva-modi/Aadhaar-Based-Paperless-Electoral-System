;/****************************************************************************
; *   heap.s:  heap assembler file for Philips LPC214x Family Microprocessors
; *
; *   Copyright(C) 2006, Philips Semiconductor
; *   All rights reserved.
; *
; *   History
; *   2005.10.01  ver 1.00    Prelimnary version, first Release
; *
;****************************************************************************/

        AREA    Heap, DATA, NOINIT

        EXPORT bottom_of_heap

bottom_of_heap    SPACE   1

        END
;/*****************************************************************************
;**                            End Of File
;*****************************************************************************/
