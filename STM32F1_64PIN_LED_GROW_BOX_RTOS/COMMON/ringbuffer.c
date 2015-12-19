
#include "RingBuffer.h"

/*!
      \fn void vfnRingBufferInit(sRingBuffer * spRingBuffer, uint8_t * StartAddress, uint8_t BufferSize)
      \brief  Initializes the desire buffer in ringbuffer
      \param  spRingBuffer: Ring Buffer struct to place the buffer data
      \param  StartAddress: Ring buffer start address
      \param  BufferSize: Ring buffer size
      \return void
*/
void ringbuffer_init(sRingBuffer * spRingBuffer, uint8_t * spStartAddress, uint16_t BufferSize)
{
	spRingBuffer->StartAddress = spStartAddress;
	spRingBuffer->EndAddress   = (spStartAddress) + (BufferSize) - 1;
	spRingBuffer->BufferSize   = BufferSize;
	spRingBuffer->pReadPointer = spStartAddress;
	spRingBuffer->pWritePointer = spStartAddress;
	spRingBuffer->BufferStatus = 0;
	spRingBuffer->write_complete = 0;
}

/*!
      \fn void vfnRingBufferReset(sRingBuffer * spRingBuffer)
      \brief  Resets both Ring buffer pointers to the start address
      \param  spRingBuffer: Ring Buffer struct to reset
      \return void
*/
void ringbuffer_reset(sRingBuffer * spRingBuffer)
{
	spRingBuffer->pReadPointer = spRingBuffer->StartAddress;
	spRingBuffer->pWritePointer = spRingBuffer->StartAddress;
	spRingBuffer->BufferStatus = 0;
	spRingBuffer->write_complete = 0;
}


/*!
      \fn void vfnRingBuffer_WriteData(sRingBuffer * psRingBuffer, uint8_t * OutData)
      \brief  Writes a single data into the buffer
      \param  spRingBuffer: Ring Buffer struct to use
      \param  OutData: 	Data to be written
      \return void
*/
void ringbuffer_write(sRingBuffer * psRingBuffer, uint8_t * OutData, uint8_t write_complete, uint8_t blocking)
{
	
	/* write data */
	*(psRingBuffer->pWritePointer) = *OutData;
	psRingBuffer->pWritePointer++;

	/* send to the beginning the pointer */
	if(psRingBuffer->pWritePointer > psRingBuffer->EndAddress)
	{
		psRingBuffer->pWritePointer = psRingBuffer->StartAddress;
	}

	if(psRingBuffer->pWritePointer == psRingBuffer->pReadPointer)
	{
		psRingBuffer->BufferStatus = RINGBUFFER_WRITE_OVERFLOW_FLAG;

		if (blocking && !write_complete)
		{
			while(psRingBuffer->BufferStatus & RINGBUFFER_WRITE_OVERFLOW_FLAG);
		}
	}

	psRingBuffer->write_complete = write_complete;

}
/*!
      \fn void vfnRingBuffer_ReadData(sRingBuffer * psRingBuffer, uint8_t * Data)
      \brief  Reads a single data into the buffer
      \param  spRingBuffer: Ring Buffer struct to use
      \param  OutData: 	Buffer to place the data
      \return void
*/
uint8_t ringbuffer_read(sRingBuffer * psRingBuffer)
{
	uint8_t data;
	data = *(psRingBuffer->pReadPointer);
	psRingBuffer->pReadPointer++;

	/* send to the beginning the pointer */
	if(psRingBuffer->pReadPointer > psRingBuffer->EndAddress)
	{
		psRingBuffer->pReadPointer = psRingBuffer->StartAddress;
	}

	if(psRingBuffer->pWritePointer == psRingBuffer->pReadPointer)
	{
		psRingBuffer->BufferStatus = RINGBUFFER_READ_OVERFLOW_FLAG;

	}
	return data;
}

uint8_t ringbuffer_is_complete(sRingBuffer * psRingBuffer)
{
	return ((psRingBuffer->BufferStatus & RINGBUFFER_READ_OVERFLOW_FLAG) && psRingBuffer->write_complete);
}
uint8_t ringbuffer_write_ready(sRingBuffer * psRingBuffer)
{
	return (!(psRingBuffer->BufferStatus & RINGBUFFER_WRITE_OVERFLOW_FLAG) && !psRingBuffer->write_complete);
}

// unused function
//static void ringbuffer_test()
//{
//	uint8_t i;
//	uint8_t write[] = {0,1,2,3,4,5,6,7,8,9};
//	uint16_t writeCount=0;
//	//uint16_t readCount = 0; unused
//	uint8_t read[sizeof(write)] = {0};
//	uint8_t buffer[5] = {0};
//	uint8_t complete =0;
//
//	sRingBuffer ring;
//	ringbuffer_init(&ring,buffer,sizeof(buffer));
//	i=0;
//	while(!ringbuffer_is_complete(&ring))
//	{
//		if(ringbuffer_write_ready(&ring))
//		{
//			complete = (writeCount == sizeof(write)-1) ? 1 : 0;
//			if(complete)
//			{
//				ringbuffer_write(&ring,write,1,0);
//				writeCount++;
//			}
//		}
//
//		if(!(ring.BufferStatus & RINGBUFFER_READ_OVERFLOW_FLAG))
//		{
//			read[i] = ringbuffer_read(&ring);
//
//			(void)read[0]; // suppress warning
//		}
//
//	}
//}
