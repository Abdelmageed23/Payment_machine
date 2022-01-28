/*********************************************************/
/* Author  : Abdelrahman Mohamed              			 */
/* Date     : 4 Jan	2022                   				 */
/* Version  : V01                            			 */
/*********************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BIT_NUM)		REG=REG|(1<<BIT_NUM)
#define CLR_BIT(REG,BIT_NUM)		REG=REG &~(1<<BIT_NUM)
#define GET_BIT(REG,BIT_NUM)		((REG>>BIT_NUM)&1)
#define TOGGLE_BIT(REG,BIT_NUM)		REG=REG^(1<<BIT_NUM)

#endif
