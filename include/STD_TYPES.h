/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Platform_Types.h
 *       Module:  -
 *
 *  Description:  Contains types that dependent on platform - CortexM4     
 *  
 *********************************************************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define WORD_LENGTH_BITS      32u
#define WORD_LENGTH_BYTES     4u
#define MSB_FIRST             0u    /* big endian bit ordering */
#define LSB_FIRST        	1u    /* little endian bit ordering */

#define HIGH_BYTE_FIRST  	0u    /* big endian byte ordering */
#define LOW_BYTE_FIRST   	1u    /* little endian byte ordering */



#define CPU_BIT_ORDER    LSB_FIRST        /*little endian bit ordering*/
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST   /*little endian byte ordering*/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef unsigned char         boolean;       /*        TRUE .. FALSE           */

typedef signed char           s8;         /*        -128 .. +127            */
typedef unsigned char         u8;         /*           0 .. 255             */
typedef volatile u8       vu8;     /*           0 .. 255             */

typedef signed short          s16;        /*      -32768 .. +32767          */
typedef unsigned short        u16;        /*           0 .. 65535           */
typedef volatile u16     vu16;       /*           0 .. 65535           */

typedef signed long           s32;        /* -2147483648 .. +2147483647     */
typedef unsigned long         u32;        /*           0 .. 4294967295      */
typedef volatile u32     vu32;     /*           0 .. 4294967295      */

typedef float                 float32;
typedef double                float64;

#ifdef STD_SUPPORT_SINT64_UINT64 /*Valid only for gnu and C99 */
typedef signed    long long  s64;   /* -9223372036854775808 .. 9223372036854775807      */
typedef unsigned  long long  u64;   /*                    0 .. 18446744073709551615     */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
typedef enum
{
	FALSE,
	TRUE,
}STD_Bool;
 
typedef enum
{
	RESET,
	SET
}STD_Status;

typedef enum
{
	DISABLE_STATE,
	ENABLE_STATE
}Functional_State;

#define NULL_PTR		(void*)0
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif  /* STD_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: STD_TYPES.h
 *********************************************************************************************************************/