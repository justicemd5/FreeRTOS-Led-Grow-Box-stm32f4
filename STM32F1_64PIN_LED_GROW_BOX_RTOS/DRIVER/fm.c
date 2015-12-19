#include "fm.h"
#include "spi.h"


//private prototypes
static ERROR_CODE Wait_Busy();
static ERROR_CODE WREN();
static ERROR_CODE WRSR(void);
static ERROR_CODE Read_Status_Register(uint8_t * const status);
static ERROR_CODE Byte_Program(uint32_t Dst, uint8_t byte);
static ERROR_CODE Enable_Write();

ERROR_CODE fm_Write(uint32_t address, uint8_t * data, uint8_t length,
					uint8_t* successful_written_bytes)
{
	ERROR_CODE err = NO_ERROR;
	uint8_t i = 0;
	uint8_t check_byte;

	if ((FM_SIZE_IN_BYTES <= (address + length))
		|| ((uint32_t)(address + length) < address))
	{
		return EXTERN_FLASH_INVALID_ADDRESS;
	}

	if (0 != successful_written_bytes)
	{
		*successful_written_bytes = 0;
	}

	for (i = 0; i < length; i++)
	{

		if (FM_EMPTY_BYTE == *(data + i)
			&& FM_EMPTY_BYTE == *(data + i + 1)
			&& FM_EMPTY_BYTE == *(data + i + 2)
			&& FM_EMPTY_BYTE == *(data + i + 3)
			&& FM_EMPTY_BYTE == *(data + i + 4))
		{
			err = EXTERN_FLASH_0xFF_WRITE;
			break;
		}

		err = fm_Read(address + i, &check_byte, 1);
		if (NO_ERROR != err)
		{
			err = EXTERN_FLASH_WRITE_ERROR;
			break;
		}

		if (FM_EMPTY_BYTE != check_byte)
		{
			err = EXTERN_FLASH_OVERWRITE_FAILED;
			break;
		}

		err = Enable_Write();
		if (NO_ERROR != err)
		{
			break;
		}

		err = Byte_Program(address + i, *(data + i));
		if (NO_ERROR != err)
		{
			break;
		}

		err = Wait_Busy();
		if (NO_ERROR != err)
		{
			err = EXTERN_FLASH_WRITE_ERROR;
			break;
		}

		err = fm_Read(address + i, &check_byte, 1);
		if (NO_ERROR != err)
		{
			err = EXTERN_FLASH_WRITE_ERROR;
			break;
		}

		if (check_byte != *(data + i))
		{
			err = EXTERN_FLASH_CORRUPTED_WRITE;
			break;
		}

		if (0 != successful_written_bytes)
		{
			*successful_written_bytes += 1;
		}
	}

	return err;
}

ERROR_CODE fm_Read(uint32_t address, uint8_t * data, uint8_t length)
{
	ERROR_CODE err;
	uint8_t i = 0;

	if (address + length >= FM_SIZE_IN_BYTES)
	{
		return EXTERN_FLASH_INVALID_ADDRESS;
	}

	spi_activate(SPI_CS_FM);

	while (1)
	{
		err = spi_write_byte(SPI_FM_REG, 0x03); //read command
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, ((0xFFFFFF & address) >> 16)); //send 3 address bytes
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, ((0xFFFF & address) >> 8));
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, 0xFF & address);
		if (NO_ERROR != err)
		{
			break;
		}

		for (i = 0; i < length; i++) //read until no_bytes is reached
		{
			err = spi_read_byte(SPI_FM_REG, (data + i));
			if (NO_ERROR != err)
			{
				break;
			}
		}

		break;
	}

	spi_deactivate();

	return err;
}

ERROR_CODE fm_Erase()
{
	ERROR_CODE err;

	err = Enable_Write();
	if (NO_ERROR != err)
	{
		return err;
	}

	spi_activate(SPI_CS_FM);

	err = spi_write_byte(SPI_FM_REG, 0x60); //send Chip Erase command (60h or C7h)

	spi_deactivate();

	if (NO_ERROR != err)
	{
		return err;
	}

	err = Wait_Busy();

	return err;
}

#ifdef TEST
ERROR_CODE fm_Test(void)
{
	ERROR_CODE err;
	uint8_t source[] = "TRING";
	uint8_t ret[] =
	{	0,0,0,0,0};
	err = fm_Write(5,&source,5, 0);
	err = fm_Read(5,&ret,5);
	if (strncmp(&source,&ret,5))
	{
		Throw(GLOBAL_ERROR);
	}

}
#endif

static ERROR_CODE Wait_Busy()
{
	ERROR_CODE err;
	uint32_t timeout = FM_TIMEOUT;
	uint8_t ret = 1;

	while ((0x01 && ret) && timeout)
	{
		err = Read_Status_Register(&ret);
		if (NO_ERROR != err)
		{
			break;
		}

		timeout--;
	}

	return err;
}

static ERROR_CODE WREN()
{
	ERROR_CODE err;

	spi_activate(SPI_CS_FM);

	err = spi_write_byte(SPI_FM_REG, 0x06); //send WREN command

	spi_deactivate();

	return err;
}

static ERROR_CODE WRSR(void)
{
	ERROR_CODE err;

	spi_activate(SPI_CS_FM);

	err = spi_write_byte(SPI_FM_REG, 0x01); //select write to status register
	if (NO_ERROR == err)
	{
		err = spi_write_byte(SPI_FM_REG, 0x00 & 0xFF); //data that will change the status of BPx or BPL (only bits 2,3,4,5,7 can be written)
	}

	spi_deactivate();

	return err;
}

static ERROR_CODE Read_Status_Register(uint8_t * const status)
{
	ERROR_CODE err;

	if (0 == status)
	{
		return INVALID_ARGUMENT;
	}

	spi_activate(SPI_CS_FM);

	err = spi_write_byte(SPI_FM_REG, 0x05); //send RDSR command
	if (NO_ERROR == err)
	{
		err = spi_read_byte(SPI_FM_REG, status); //receive byte
	}

	spi_deactivate();

	return err;
}

static ERROR_CODE Byte_Program(uint32_t address, uint8_t byte)
{
	ERROR_CODE err;

	spi_activate(SPI_CS_FM);

	while (1)
	{
		err = spi_write_byte(SPI_FM_REG, 0x02); //send Byte Program command
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, ((0xFFFFFF & address) >> 16)); //send 3 address bytes
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, ((0xFFFF & address) >> 8));
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, 0xFF & address);
		if (NO_ERROR != err)
		{
			break;
		}

		err = spi_write_byte(SPI_FM_REG, byte); //send byte to be programmed

		break;
	}

	spi_deactivate();

	return err;
}

static ERROR_CODE Enable_Write()
{
	ERROR_CODE err;
	uint32_t timeout = FM_TIMEOUT;
	uint8_t ret = 0;

	err = Read_Status_Register(&ret);
	if (NO_ERROR != err)
	{
		return err;
	}

	while ((0 != (0x1C & ret)) && timeout) //da li su BP0, BP1, BP2 bitovi zakljuèani?
	{
		WREN();
		WRSR(); //odblokirati upis - BPL=0

		err = Read_Status_Register(&ret);
		if (NO_ERROR != err)
		{
			return err;
		}

		timeout--;
	}
	if (0 == timeout)
	{
		return EXTERN_FLASH_WRITE_ERROR;
	}
	//bitovi su otkljuèani
	//da li je Write Enable?
	timeout = FM_TIMEOUT;
	while ((0x02 != ret) && timeout)
	{
		WREN();

		err = Read_Status_Register(&ret);
		if (NO_ERROR != err)
		{
			return err;
		}

		timeout--;
	}
	if (0 == timeout)
	{
		return EXTERN_FLASH_WRITE_ERROR;
	}

	return NO_ERROR;
}

ERROR_CODE fm_peripheral_Test()
{
	uint8_t read[2] = { 0, 0 };

	ERROR_CODE err = fm_Read(4, &read, 2);
	if ((NO_ERROR == err) && (('A' != read[0]) || ('G' != read[1])))
	{
		err = TEST_FM_FAILED;
	}

	return err;
}

