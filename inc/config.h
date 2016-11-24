/*
 * config.h
 *
 *  Created on: 24 lis 2016
 *      Author: konrad
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// -- Bluetooth Low Energy module (USART)
// bluetooth gpio port -> A
#define BT_USART_PORT		(USART1)
#define BT_USART_BAUD		(115200)
#define BT_USART_IRQN		(USART1_IRQn)

// -- OLED display module (I2C)
#define LCD_I2C_PORT		(I2C1)
#define LCD_I2C_PINS		(GPIO_Pin_6 | GPIO_Pin_7)
#define LCD_RCC_I2C			(RCC_APB1Periph_I2C1)
#define LCD_RCC_GPIO		(RCC_APB2Periph_GPIOB)
#define LCD_GPIO_PORT		(GPIOB)



#endif /* CONFIG_H_ */
