#include "APP/APP.h"

void main()
{
	/*ATM initialization*/
	ATM_Init();

	while(1)
	{
		/*Start ATM program*/
		ATM_Prog_Mode();
	}
}
