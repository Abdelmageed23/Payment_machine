/*********************************************************/
/* Author  : Abdelrahman Mohamed              			 */
/* Date     : 6 Jan	2022                   				 */
/* Version  : V01                            			 */
/*********************************************************/

#include "../../01-LIB/BIT_MATH.h"
#include "../../01-LIB/STD_TYPES.h"

#include "Interrupt_interface.h"
#include "Interrupt_private.h"
#include "Interrupt_config.h"

void GlobalInerruptEnable(void)
{
	SET_BIT(SREG,7);
}
