/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "stm32f746g_discovery_sdram.h"
#include "stm32f7xx_hal_rcc.h"
#include "stm32f7xx_hal_gpio.h"
#include <string.h>

#if !GFX_USE_OS_CHIBIOS
	#define AFRL	AFR[0]
	#define AFRH	AFR[1]
#endif

static const ltdcConfig driverCfg = {
	480, 272,								// Width, Height (pixels)
	41, 10,									// Horizontal, Vertical sync (pixels)
	13, 2,									// Horizontal, Vertical back porch (pixels)
	32, 2,									// Horizontal, Vertical front porch (pixels)
	0,										// Sync flags
	0x000000,								// Clear color (RGB888)

	{										// Background layer config
		(LLDCOLOR_TYPE *)SDRAM_DEVICE_ADDR, // Frame buffer address
		480, 272,							// Width, Height (pixels)
		480 * LTDC_PIXELBYTES,				// Line pitch (bytes)
		LTDC_PIXELFORMAT,					// Pixel format
		0, 0,								// Start pixel position (x, y)
		480, 272,							// Size of virtual layer (cx, cy)
		LTDC_COLOR_FUCHSIA,					// Default color (ARGB8888)
		0x980088,							// Color key (RGB888)
		LTDC_BLEND_FIX1_FIX2,				// Blending factors
		0,									// Palette (RGB888, can be NULL)
		0,									// Palette length
		0xFF,								// Constant alpha factor
		LTDC_LEF_ENABLE						// Layer configuration flags
	},

	LTDC_UNUSED_LAYER_CONFIG				// Foreground layer config
};

/* Display timing */
#define RK043FN48H_FREQUENCY_DIVIDER	5

static void configureLcdPins(void)
{
	// Enable GPIOs clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;	// GPIOE
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;	// GPIOG
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;	// GPIOI
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;	// GPIOJ
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;	// GPIOK

	// PI15: LCD_R0
	GPIOI->MODER |= GPIO_MODER_MODER15_1;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_15;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR15_1;
	GPIOI->AFRH |= ((uint32_t)0xE << 4*7);

	// PJ0: LCD_R1
	GPIOJ->MODER |= GPIO_MODER_MODER0_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_0;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0 | GPIO_OSPEEDER_OSPEEDR0_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*0);

	// PJ1: LCD_R2
	GPIOJ->MODER |= GPIO_MODER_MODER1_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_1;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*1);

	// PJ2: LCD_R3
	GPIOJ->MODER |= GPIO_MODER_MODER2_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_2;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_0 | GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*2);

	// PJ3: LCD_R4
	GPIOJ->MODER |= GPIO_MODER_MODER3_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_3;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0 | GPIO_OSPEEDER_OSPEEDR3_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*3);

	// PJ4: LCD_R5
	GPIOJ->MODER |= GPIO_MODER_MODER4_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_4;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0 | GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*4);

	// PJ5: LCD_R6
	GPIOJ->MODER |= GPIO_MODER_MODER5_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_5;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*5);

	// PJ6: LCD_R7
	GPIOJ->MODER |= GPIO_MODER_MODER6_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_6;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0 | GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*6);

	// PJ7: LCD_G0
	GPIOJ->MODER |= GPIO_MODER_MODER7_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_7;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_0 | GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOJ->AFRL |= ((uint32_t)0xE << 4*7);

	// PJ8: LCD_G1
	GPIOJ->MODER |= GPIO_MODER_MODER8_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_8;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_0 | GPIO_OSPEEDER_OSPEEDR8_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*0);

	// PJ9: LCD_G2
	GPIOJ->MODER |= GPIO_MODER_MODER9_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_9;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*1);

	// PJ10: LCD_G3
	GPIOJ->MODER |= GPIO_MODER_MODER10_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_10;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*2);

	// PJ11: LCD_G4
	GPIOJ->MODER |= GPIO_MODER_MODER11_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_11;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_0 | GPIO_OSPEEDER_OSPEEDR11_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*3);

	// PK0: LCD_G5
	GPIOK->MODER |= GPIO_MODER_MODER0_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_0;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0 | GPIO_OSPEEDER_OSPEEDR0_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*0);

	// PK1: LCD_G6
	GPIOK->MODER |= GPIO_MODER_MODER1_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_1;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*1);

	// PK2: LCD_G7
	GPIOK->MODER |= GPIO_MODER_MODER2_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_2;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_0 | GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*2);

	// PE4: LCD_B0
	GPIOE->MODER |= GPIO_MODER_MODER4_1;
	GPIOE->OTYPER &=~ GPIO_OTYPER_OT_4;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0 | GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOE->AFRL |= ((uint32_t)0xE << 4*4);

	// PJ13: LCD_B1
	GPIOJ->MODER |= GPIO_MODER_MODER13_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_13;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_0 | GPIO_OSPEEDER_OSPEEDR13_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*5);

	// PJ14: LCD_B2
	GPIOJ->MODER |= GPIO_MODER_MODER14_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_14;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_0 | GPIO_OSPEEDER_OSPEEDR14_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*6);

	// PJ15: LCD_B3
	GPIOJ->MODER |= GPIO_MODER_MODER15_1;
	GPIOJ->OTYPER &=~ GPIO_OTYPER_OT_15;
	GPIOJ->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR15_1;
	GPIOJ->AFRH |= ((uint32_t)0xE << 4*7);

	// PG12: LCD_B4
	GPIOG->MODER |= GPIO_MODER_MODER12_1;
	GPIOG->OTYPER &=~ GPIO_OTYPER_OT_12;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_0 | GPIO_OSPEEDER_OSPEEDR12_1;
	GPIOG->AFRH |= ((uint32_t)0x9 << 4*4);

	// PK4: LCD_B5
	GPIOK->MODER |= GPIO_MODER_MODER4_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_4;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0 | GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*4);

	// PK5: LCD_B6
	GPIOK->MODER |= GPIO_MODER_MODER5_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_5;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*5);

	// PK6: LCD_B7
	GPIOK->MODER |= GPIO_MODER_MODER6_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_6;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0 | GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*6);

	// PK7: LCD_DE
	GPIOK->MODER |= GPIO_MODER_MODER7_1;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_7;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_0 | GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOK->AFRL |= ((uint32_t)0xE << 4*7);

	// PI9: LCD_VSYNC
	GPIOI->MODER |= GPIO_MODER_MODER9_1;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_9;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOI->AFRH |= ((uint32_t)0xE << 4*1);

	// PI10: LCD_VSYNC
	GPIOI->MODER |= GPIO_MODER_MODER10_1;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_10;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOI->AFRH |= ((uint32_t)0xE << 4*2);

	// PI13: LCD_INT
	GPIOI->MODER |= GPIO_MODER_MODER13_1;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_13;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_0 | GPIO_OSPEEDER_OSPEEDR13_1;
	GPIOI->AFRH |= ((uint32_t)0xE << 4*5);

	// PI14: LCD_CLK
	GPIOI->MODER |= GPIO_MODER_MODER14_1;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_14;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_0 | GPIO_OSPEEDER_OSPEEDR14_1;
	GPIOI->AFRH |= ((uint32_t)0xE << 4*6);

	// PI8: ???
	GPIOI->MODER |= GPIO_MODER_MODER8_1;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_8;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_0 | GPIO_OSPEEDER_OSPEEDR8_1;
	GPIOI->AFRH |= ((uint32_t)0xE << 4*0);

	// PI12: LCD_DISP_PIN
	GPIOI->MODER |= GPIO_MODER_MODER12_0;
	GPIOI->OTYPER &=~ GPIO_OTYPER_OT_12;
	GPIOI->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_0 | GPIO_OSPEEDER_OSPEEDR12_1;

	// PK3: LCD_BL_CTRL
	GPIOK->MODER |= GPIO_MODER_MODER3_0;
	GPIOK->OTYPER &=~ GPIO_OTYPER_OT_3;
	GPIOK->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0 | GPIO_OSPEEDER_OSPEEDR3_1;
}

static GFXINLINE void init_board(GDisplay *g) {

	// As we are not using multiple displays we set g->board to NULL as we don't use it
	g->board = 0;

	switch(g->controllerdisplay) {
	case 0:

		// Set pin directions
		configureLcdPins();

		// Enable the display and turn on the backlight
		GPIOI->ODR |= (1 << 12);	// PowerOn
		GPIOK->ODR |= (1 << 3);		// Backlight on

		#define STM32_SAISRC_NOCLOCK    (0 << 23)   /**< No clock.                  */
		#define STM32_SAISRC_PLL        (1 << 23)   /**< SAI_CKIN is PLL.           */
		#define STM32_SAIR_DIV2         (0 << 16)   /**< R divided by 2.            */
		#define STM32_SAIR_DIV4         (1 << 16)   /**< R divided by 4.            */
		#define STM32_SAIR_DIV8         (2 << 16)   /**< R divided by 8.            */
		#define STM32_SAIR_DIV16        (3 << 16)   /**< R divided by 16.           */

		// RK043FN48H LCD clock configuration
		// PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz
		// PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz
		// PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz
		// LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz
		#define STM32_PLLSAIN_VALUE                 192
		#undef STM32_PLLSAIQ_VALUE
		#define STM32_PLLSAIQ_VALUE                 7
		#undef STM32_PLLSAIR_VALUE
		#define STM32_PLLSAIR_VALUE                 RK043FN48H_FREQUENCY_DIVIDER
		#define STM32_PLLSAIR_POST                  STM32_SAIR_DIV4
		RCC->PLLSAICFGR = (STM32_PLLSAIN_VALUE << 6) | (STM32_PLLSAIR_VALUE << 28) | (STM32_PLLSAIQ_VALUE << 24);
		RCC->DCKCFGR1 = (RCC->DCKCFGR1 & ~RCC_DCKCFGR1_PLLSAIDIVR) | STM32_PLLSAIR_POST;
		RCC->CR |= RCC_CR_PLLSAION;

		// Initialise the SDRAM
		BSP_SDRAM_Init();

		// Clear the SDRAM
		//memset((void *)SDRAM_BANK_ADDR, 0, 0x400000);

		break;
	}
}

static GFXINLINE void post_init_board(GDisplay* g) {
	(void) g;
}

static GFXINLINE void set_backlight(GDisplay* g, uint8_t percent) {
	(void) g;

	// ST was stupid enought not to hook this up to a pin that
	// is able to act as PWM output...
	if (percent <= 0) {
		GPIOK->ODR &=~ (1 << 3);	// Backlight off
	} else {
		GPIOK->ODR |= (1 << 3);		// Backlight on
	}
}

#endif /* _GDISP_LLD_BOARD_H */
