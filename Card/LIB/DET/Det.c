 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *
 * Author: Abdalla Abdelhafiz
 ******************************************************************************/

#include "../STD_TYPES.h"
#include "Det.h"

static uint8_t index_row=0;

void Det_ReportError( uint8_t ModuleId , uint8_t ApiId)
{
gu8arr_error[index_row][0]=ModuleId;
gu8arr_error[index_row][1]=ApiId;
index_row++;
}

