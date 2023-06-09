/*
 * BIT_MATH.h
 *
 * Created: 5/1/2022 6:03:17 PM
 *  Author: Ahmed Aboraya
 */


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/**********************************************************************************************************************
 *  GLOBAL DATA DEFITNITIONS
 *********************************************************************************************************************/

enum BitsCount{
    ONE_BIT = 1,
    TWO_BITS,
    THREE_BITS,
    FOUR_BITS,
    FIVE_BITS,
    SIX_BITS,
    SEVEN_BITS,
	EIGHT_BITS,
    NINE_BITS,
    TEN_BITS,
    ELEVEN_BITS,
    TWELVE_BITS,
    THIRTEEN_BITS,
    FOURTEEN_BITS,
    FIFTEEN_BITS,
    SIXTEEN_BITS,
    SEVENTEEN_BITS,
    EIGHTEEN_BITS,
    NINETEEN_BITS,
    TWENTY_BITS,
    TWENTYONE_BITS,
    TWENTYTWO_BITS,
    TWENTYTHREE_BITS,
    TWENTYFOUR_BITS,
    TWENTYFIVE_BITS,
    TWENTYSIX_BITS,
    TWENTYSEVEN_BITS,
    TWENTYEIGHT_BITS,
    TWENTYNINE_BITS,
    THIRTY_BITS,
    THIRTYONE_BITS,


};

//@ Bit_id_options
enum BitId{
    BIT0,
    BIT1,
    BIT2,
    BIT3,
    BIT4,
    BIT5,
    BIT6,
    BIT7,
    BIT8,
    BIT9,
    BIT10,
    BIT11,
    BIT12,
    BIT13,
    BIT14,
    BIT15,
    BIT16,
    BIT17,
    BIT18,
    BIT19,
    BIT20,
    BIT21,
    BIT22,
    BIT23,
    BIT24,
    BIT25,
    BIT26,
    BIT27,
    BIT28,
    BIT29,
    BIT30,
    BIT31,
};

/**********************************************************************************************************************
 *  FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define SET_BIT(REG, BIT)		(REG |= (1<<BIT))
#define CLEAR_BIT(REG,BIT)		(REG &=~ (1<<BIT))
#define TOGGLE_BIT(REG,BIT)		(REG ^= (1<<BIT))
#define GET_BIT(REG,BIT)		((REG >> BIT) & 1)

#define SET_PIN(REG, PIN)		(REG |= PIN)
#define CLEAR_PIN(REG, PIN)		(REG &=~ PIN)
#define TOGGLE_PIN(REG, PIN)	(REG ^= PIN)

#define SET_CONFIG(REG, CONFIG)			SET_PIN(REG, CONFIG)
#define CLEAR_CONFIG(REG, CONFIG)		(REG &= CONFIG)
#define SET_REG(REG)					(REG = ~0x00)
#define CLEAR_REG(REG)				    (REG = 0X00)
#define WRITE_REG(REG, VALUE)			(REG = VALUE)
#define READ_REG(REG)			        (REG)

#define MASK(LEN)				 	(( 1<<(LEN))-1)
#define BITS_MASK(START,LEN) 		( MASK(LEN)<<(START) )

#define WRITE_BITS(REG, MASK, VALUE)  	(REG = ((REG & ~(MASK)) | ((VALUE) & (MASK))))

#define	READ_BITS(VAR,START,LEN)		((VAR & (BITS_MASK(START,LEN)) )>>START)
#define ASSIGN_BITS(VAR,START,LEN,VAL)		(VAR =	(VAR & (~( (BITS_MASK(START,LEN)) ))) | ( ((VAL<<START)&BITS_MASK(START,LEN))))
#define ASSIGN_BIT(VAR,START,VAL)			ASSIGN_BITS(VAR,START,ONE_BIT,VAL)


#define ASSIGN_PARAM(REG, PARAM)		(PARAM < 0 ? CLEAR_CONFIG(REG, PARAM) :  SET_CONFIG(REG, PARAM))
#define SET_BITFIELD(BITFIELD)			(BITFIELD = 1)
#define CLEAR_BITFIELD(BITFIELD)		(BITFIELD = 0)
#endif /* BIT_MATH_H_ */
