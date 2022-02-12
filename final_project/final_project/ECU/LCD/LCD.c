
/*
1- Macros
2- Implementation of functions
*/

#include "LCD.h"
#include <util/delay.h>
#include "../../MCAL/Atmega32_Registers.h"


/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/



void LCD_Init(void)/*Initialize LCD*/
{
	/*Define direction for command pins*/
	DIO_SetDir(LCD_CMD_PORT, LCD_RS, LCD_OUTPUT);
	DIO_SetDir(LCD_CMD_PORT, LCD_RW, LCD_OUTPUT);
	DIO_SetDir(LCD_CMD_PORT, LCD_EN, LCD_OUTPUT);
	/*Define direction for data pins*/
	DIO_SetDir(LCD_DTA_PORT, LCD_D4, LCD_OUTPUT);
	DIO_SetDir(LCD_DTA_PORT, LCD_D5, LCD_OUTPUT);
	DIO_SetDir(LCD_DTA_PORT, LCD_D6, LCD_OUTPUT);
	DIO_SetDir(LCD_DTA_PORT, LCD_D7, LCD_OUTPUT);
	/*LCD controller is slower than MC speed*/
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	/* Return Home  */
	LCD_WriteCMD(LCD_HOME_CMD);
	_delay_ms(15);

	/* Function Set  */
	LCD_WriteCMD(LCD_FUNCTION_SET_CMD);
	_delay_ms(1);

	/* Display ON / OFF Control */
	LCD_WriteCMD(LCD_CONTROL_CMD);
	_delay_ms(1);

	/* Clear Display */
	LCD_WriteCMD(LCD_CLEAR_CMD);
	_delay_ms(15);

	/* Entry Mode Set  */
	LCD_WriteCMD(LCD_MODE_CMD);
	_delay_ms(2);
	/*
//	we can write the values direct without MACROS
//	LCD_WriteCMD(0x02);
//	LCD_WriteCMD(0x28);
//	LCD_WriteCMD(0x0C);
//	LCD_WriteCMD(0x01);
//	LCD_WriteCMD(0x06);
	*/
}
void LCD_WriteCMD(uint8 cmd)   /*Write command inside control register*/
{
	/*RS is logic(0) to write inside control register*/
	DIO_SetLow(LCD_CMD_PORT, LCD_RS);
	/*RW is logic(0) to write on LCD*/
	DIO_SetLow(LCD_CMD_PORT, LCD_RW);
	/*To be sure of enable state before start operation*/
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Send high nibble of command*/
	PORTA = (cmd & 0xF0) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*send low nibble of command*/
	PORTA = (cmd << 4) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Delay for 2 millisecond*/
	_delay_ms(2);
}
void LCD_WriteChar(uint8 data)/*write data inside data register*/
{
	/*RS is logic(1) to write inside data register*/
	DIO_SetHigh(LCD_CMD_PORT, LCD_RS);
	/*RW is logic(0) to write on LCD*/
	DIO_SetLow(LCD_CMD_PORT, LCD_RW);
	/*To be sure of enable state before start operation*/
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Send high nibble of command*/
	PORTA = (data & 0xF0) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*send low nibble of command*/
	PORTA = (data << 4) | (PORTA & 0x0F);
	DIO_SetHigh(LCD_CMD_PORT, LCD_EN);
	_delay_ms(1);
	DIO_SetLow(LCD_CMD_PORT, LCD_EN);
	/*Delay for 2 millisecond*/
	_delay_ms(2);
}
void LCD_WriteString(uint8 string[])/*write string on screen*/
{
	while(*string != '\0')
	{
		LCD_WriteChar(*string);
		string++;
	}
}
void LCD_WriteNumbers(uint32 numbr)
{
	uint8 num[10];
	ltoa(numbr, (uint8*)num, 10);//Long to Ascii
	LCD_WriteString(num);
}
void LCD_Clear(void)/*Clear data display on screen*/
{
	LCD_WriteCMD(0x01);
}

void LCD_WriteAtPosition(uint8 lineNumber , uint8 digitNumber)
{
	if ( (digitNumber>0 && digitNumber<=15) && (lineNumber>1 && lineNumber<=2) )
	{
	    switch(lineNumber)
	    {
		    case 1:
		    	LCD_WriteCMD(digitNumber+127);   // 127 (0x80) if the offset address of line 1 in DDRAM at LM06
		    break;
		    case 2:
		    	LCD_WriteCMD(digitNumber+191);	// 191 (0xBF) if the offset address of line 1 in DDRAM at LM06
		    break;
		    default:
		    break;
	    }
	}
}

