
// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.

#include "EXTI_LedApp.c"
#include "EXTI_NestedApp.c"

/**********************************************************************************************************************
 *  FUNCTION PROTOTYPE
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  MAIN FUNCTION
 *********************************************************************************************************************/

int main()
{
	//App Toggle Led based on the exti0 from the falling edge of the push button
	//EXTI_LedApp();

	EXTI_NestedApp();
}



