#include "main.h"

static volatile uint32_t sysTickCnt = 0;

static inline void configureGPIO(void);

extern uint16_t ClkStatus;

/**
 **===========================================================================
 **
 **  - Configures GPIO ports
 **  - Configures SysTick for 100mS interval
 **  - Turns on LED attached to PA5 (active high)
 **
 **===========================================================================
 */
int main(void) {

	if (ClkStatus != RESET) {

		configureGPIO();
		SysTick_Config((uint32_t) 0x00802C7F);

		// turn PA5 on
		GPIOA->ODR |= GPIO_ODR_ODR_5;

		/* Infinite loop */
		while (1) {

		}
	} else{

		// clock configuration did not complete successfully - enter loop and do nothing
		while(1){

		}
	}

}

/*
 * Configures GPIO ports
 * 	- sets PA5 as output
 *
 * NOTE: to enable clocks for specific ports see system_stm32f4xx.c
 */
static inline void configureGPIO(void) {
	GPIOA->MODER &= ~(GPIO_MODER_MODER5);
	GPIOA->MODER |= (GPIO_MODER_MODER5_0);
}

/*
 * Toggles the state of PA5 every second
 */
void SysTick_Handler(void) {
	if (++sysTickCnt > 9) {
		GPIOA->ODR ^= GPIO_ODR_ODR_5;
		sysTickCnt = 0;
	}
}
