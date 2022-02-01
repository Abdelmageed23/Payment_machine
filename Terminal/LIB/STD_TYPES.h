/*********************************************************/
/* Author  : Abdelrahman Mohamed              			 */
/* Date     : 4 Jan	2022                   				 */
/* Version  : V01                            			 */
/*********************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H
#define NULL_PTR          ((void *)0)

#ifndef STD_ON
#define STD_ON     0x01U /* Standard ON   */
#endif
#ifndef STD_OFF
#define STD_OFF    0x00U /* Standard OFF  */
#endif
#ifndef STD_HIGH
#define STD_HIGH   0x01U /* Standard HIGH */
#endif
#ifndef STD_LOW
#define STD_LOW    0x00U /* Standard LOW  */
#endif

/*
 * Boolean Values
 */
#ifndef FALSE
#define FALSE (0u)
#endif
#ifndef TRUE
#define TRUE (1u)
#endif



typedef unsigned char 			uint8_t; ;
typedef unsigned short int		uint16_t;
typedef unsigned long  int		uint32_t;
typedef unsigned long long 		uint64_t;

typedef float f32;
typedef double f64;
typedef long double f128;


typedef signed char 			sint8_t;
typedef signed short int 		sint16_t;
typedef signed long int			sint32_t;
typedef signed long long 		sint64_t;



#define NULL 0
#define Null_pointer 0
#define OK 1
#define NOK 0
#define BUSY	3
#define IDLE	1
#endif
