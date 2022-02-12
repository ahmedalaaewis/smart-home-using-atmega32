

#ifndef LCD_H_
#define LCD_H_

/*
What should i write here!
1- Macros
2- User defined data types (Structure - Union - Enumeration)
3- Global variables (if Exist)
4- Functions prototypes
*/

#include "LCD_CONFIG.h"
#define LCD_HOME_CMD  			 0X02 		 // return cursor to first position on first line

#define LCD_CLEAR_CMD  			 0X01 		 // replace all characters with ASCII 'space'

#define LCD_DISPLY_ON      		 0x04         // Display on
#define LCD_DISPLY_OFF     		 0x00         // Display off
#define LCD_CURSER_ON      		 0x02         // cursor on
#define LCD_CURSER_OFF     		 0x00         // cursor off
#define LCD_BLINK_ON       		 0x01         // cursor blink on
#define LCD_BLINK_OFF      		 0x00         // cursor blink off
#define LCD_CONTROL_OPCODE 		 0x08
#define LCD_CONTROL_CMD    		 ( LCD_CONTROL_OPCODE | LCD_DISPLY_ON | LCD_CURSER_ON | LCD_BLINK_OFF )

#define LCD_8_BIT_DATA           0x10         // 8-bit data
#define LCD_4_BIT_DATA           0x00         // 4-bit data
#define LCD_2_LINE               0x08         // 2-line display
#define LCD_1_LINE               0x00         // 1-line display
#define LCD_FONT_BOLD            0x04         // 5 x 10 font
#define LCD_FONT_NOT_BOLD        0x00         // 5 x 8 font
#define LCD_FUNCTION_SET_OPCODE  0x20
#define LCD_FUNCTION_SET_CMD     ( LCD_FUNCTION_SET_OPCODE | LCD_4_BIT_DATA | LCD_2_LINE | LCD_FONT_NOT_BOLD )

#define LCD_RIGHT_SHIFT       	 0x02         // shift cursor from left to right on read/write
#define LCD_LIFT_SHIFT       	 0x00         // shift cursor from right TO left on read/write
#define LCD_STOP_SHIFT      	 0x01
#define LCD_MODE_OPCODE 		 0x03
#define LCD_MODE_CMD    		 ( LCD_MODE_OPCODE | LCD_MODE_OPCODE)
void LCD_Init(void);              								 /*Initialize LCD*/
void LCD_WriteCMD(uint8 cmd);   								/*Write command inside control register*/
void LCD_WriteChar(uint8 data);   								/*write data inside data register*/
void LCD_WriteString(uint8 string[]);  								/*write string on screen*/
void LCD_WriteNumbers(uint32 numbr);							/*write number on screen*/
void LCD_WriteAtPosition(uint8 lineNumber , uint8 digitNumber);/*write number on specific position on screen*/
void LCD_Clear(void);              								/*Clear data display on screen*/

#endif /* LCD_H_ */
