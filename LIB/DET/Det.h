 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.h
 *
 * Description:  Det stores the development errors reported by other modules.
 *
 * Author: Abdalla Abdelhafiz
 ******************************************************************************/

#ifndef DET_H
#define DET_H


uint8_t gu8arr_error[50][2];    // array that holds all errors

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
void Det_ReportError( uint8_t ModuleId, uint8_t ApiId); // call this function to report an error

#endif /* DET_H */