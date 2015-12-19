/****************************************************************************************************/
/**
Copyright (c) 2008 Freescale Semiconductor
Freescale Confidential Proprietary
\file       RingBuffer.h
\brief
\author     Freescale Semiconductor
\author     Guadalajara Applications Laboratory RTAC Americas
\author     b22385
\version    0.1
\date       Sep 12, 2011
*/
/****************************************************************************************************/
/*                                                                                                  */
/* All software, source code, included documentation, and any implied know-how are property of      */
/* Freescale Semiconductor and therefore considered CONFIDENTIAL INFORMATION.                       */
/* This confidential information is disclosed FOR DEMONSTRATION PURPOSES ONLY.                      */
/*                                                                                                  */
/* All Confidential Information remains the property of Freescale Semiconductor and will not be     */
/* copied or reproduced without the express written permission of the Discloser, except for copies  */
/* that are absolutely necessary in order to fulfill the Purpose.                                   */
/*                                                                                                  */
/* Services performed by FREESCALE in this matter are performed AS IS and without any warranty.     */
/* CUSTOMER retains the final decision relative to the total design and functionality of the end    */
/* product.                                                                                         */
/* FREESCALE neither guarantees nor will be held liable by CUSTOMER for the success of this project.*/
/*                                                                                                  */
/* FREESCALE disclaims all warranties, express, implied or statutory including, but not limited to, */
/* implied warranty of merchantability or fitness for a particular purpose on any hardware,         */
/* software ore advise supplied to the project by FREESCALE, and or any product resulting from      */
/* FREESCALE services.                                                                              */
/* In no event shall FREESCALE be liable for incidental or consequential damages arising out of     */
/* this agreement. CUSTOMER agrees to hold FREESCALE harmless against any and all claims demands or */
/* actions by anyone on account of any damage,or injury, whether commercial, contractual, or        */
/* tortuous, rising directly or indirectly as a result of the advise or assistance supplied CUSTOMER*/
/* in connectionwith product, services or goods supplied under this Agreement.                      */
/*                                                                                                  */
/****************************************************************************************************/

/*****************************************************************************************************
* Module definition against multiple inclusion
*****************************************************************************************************/

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
/*****************************************************************************************************
* Include files
*****************************************************************************************************/
/*****************************************************************************************************
* Declaration of project wide TYPES
*****************************************************************************************************/
/*!
    \enum eRingBufferFlags
    \brief Ringbuffer state flags
*/
#include "stdint.h"

#define RINGBUFFER_WRITE_OVERFLOW_FLAG	1
#define RINGBUFFER_READ_OVERFLOW_FLAG	2
#define RINGBUFFER_WRITE_COMPLETE_FLAG	4
#define RINGBUFFER_READ_COMPLETE_FLAG	8
/*!
    \enum sRingBuffer
    \brief Struct for ring buffer
*/
typedef struct
{
	volatile uint8_t	* pWritePointer;
	volatile uint8_t	* pReadPointer;
	uint8_t * StartAddress;
	uint8_t * EndAddress;
	uint16_t BufferSize;
	volatile uint8_t BufferStatus;
	volatile uint8_t write_complete;

}sRingBuffer;
/*****************************************************************************************************
* Definition of project wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of project wide MACROS / #DEFINE-CONSTANTS
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of project wide FUNCTIONS
*****************************************************************************************************/
void ringbuffer_init(sRingBuffer * spRingBuffer, uint8_t * spStartAddress, uint16_t BufferSize);
void ringbuffer_reset(sRingBuffer * spRingBuffer);
void ringbuffer_write(sRingBuffer * psRingBuffer, uint8_t * OutData, uint8_t write_complete, uint8_t blocking);
uint8_t ringbuffer_read(sRingBuffer * psRingBuffer);
uint8_t ringbuffer_is_complete(sRingBuffer * psRingBuffer);
uint8_t ringbuffer_write_ready(sRingBuffer * psRingBuffer);

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs - NOT for use in other modules
*****************************************************************************************************/

#endif /*RINGBUFFER_H_*/

