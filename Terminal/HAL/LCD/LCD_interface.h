#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

/*Send command function that takes a binary data and return void*/
void LCD_sendComd(uint8_t u8_Data);

/*Send data function that takes a char and return void*/
void LCD_sendData(uint8_t u8_Data);

/*Send string function that takes a string data and return void*/
void LCD_sendStrData(uint8_t* pu8_Data);

/*Access a specific location function that takes x and y and return void*/
void LCD_GoToXY(uint8_t u8_Xpos,uint8_t u8_Ypos);

/*Clear LCD function that takes void and return void*/
void LCD_CLR(void);

void LCD_SetSpecialChar(uint8_t* pu8_Arr,uint8_t BlockNUM,uint8_t u8_Xpos,uint8_t u8_Ypos);

/*Send number function that takes a number and return void*/
void LCD_WriteNumber(uint32_t u32_NUM);

/*LCD initialization function*/
void LCD_init(void);

#endif
