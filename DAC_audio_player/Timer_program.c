
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_reg.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "PORT_register.h"
#include <avr/pgmspace.h>
#define preload    (u8)131
extern unsigned char untitled_raw[15697];
void (*Timer_Pfunc)(void);
void  Timer0_voidInit(void)
{
	CLEAR_BIT(TCCR0,3);
	CLEAR_BIT(TCCR0,6);
	//ovInterrupt
	SET_BIT(TIMSK,0);
	//enbale  global intterrupt
	SET_BIT(SERG,7);
	//preload value
	TCNT0=131;
	//prescalar to 8
	CLEAR_BIT(TCCR0,0);
	SET_BIT(TCCR0,1);
	CLEAR_BIT(TCCR0,2);
}
void TIMER0_voidSetCallBack(void (*pfunc)(void))
{
	Timer_Pfunc=pfunc;
}

void __vector_11(void)
{
	static u16 local_u16counter=0;

	/*if(local_u16counter==1000)
	{
		local_u16counter=0;
		Timer_Pfunc();
	}*/
	TCNT0=preload;
	PORTA=pgm_read_byte(&untitled_raw[local_u16counter]);
	local_u16counter++;
	if(local_u16counter==15697)
	{
		local_u16counter=0;
		//Timer_Pfunc();
	}
}
