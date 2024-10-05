/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdbool.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t contador = 0;
int estadoBoton;
int modo;
int sumar;
int restar;
unsigned long lastDebounceTimeBot1 = 0;
unsigned long lastDebounceTimeBot2 = 0;
unsigned long lastDebounceTimeBot3 = 0;
unsigned long debounceDelay = 50;

bool lastButtonStateBot1 = 0;
bool lastButtonStateBot2 = 0;
bool lastButtonStateBot3 = 0;
/* USER CODE END PV */
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
    {
  	  int readingBot1 = HAL_GPIO_ReadPin(B_modo_GPIO_Port, B_modo_Pin);
  	  int readingBot2 = HAL_GPIO_ReadPin(B_inc_GPIO_Port, B_inc_Pin);
  	  int readingBot3 = HAL_GPIO_ReadPin(B_dec_GPIO_Port, B_dec_Pin);
  	  uint32_t currentTime = HAL_GetTick();

  	  //boton modo
  	  if (readingBot1 != lastButtonStateBot1) {
  	    lastDebounceTimeBot1 = currentTime;
  	  }
  	  if((currentTime - lastDebounceTimeBot1) > debounceDelay){
  		  if (readingBot1 != estadoBoton) {
  			  estadoBoton = readingBot1;
  			  if (estadoBoton == 1) {
  				  modo = !modo;
  			  }
  	    }
  	  }
  	  lastButtonStateBot1 = readingBot1;

  	  //boton resta
  	  if (readingBot2 != lastButtonStateBot2) {
  	      lastDebounceTimeBot2 = currentTime;
  	    }
  	  if ((currentTime - lastDebounceTimeBot2) > debounceDelay) {
  	      if (readingBot2 != restar) {
  	        restar = readingBot2;
  	        if (restar == 1) {
  	          contador--;
  	        }
  	      }
  	    }
  	  lastButtonStateBot2 = readingBot2;

  	  // Anti-rebote para BOT3
  	    if (readingBot3 != lastButtonStateBot3) {
  	      lastDebounceTimeBot3 = currentTime;
  	    }
  	    if((currentTime - lastDebounceTimeBot3) > debounceDelay) {
  	      if (readingBot3 != sumar) {
  	        sumar = readingBot3;
  	        if (sumar == 1) {
  	          contador++;
  	          if (modo == 1) {
  	            if (contador > 4) {
  	              contador = 0;
  	            }
  	          }
  	          else {
  	            if (contador > 15) {
  	              contador = 0;
  	            }
  	          }
  	        }
  	      }
  	    }
  	    lastButtonStateBot3 = readingBot3;

  	  if(modo == 0){
  		  switch(contador){
  		  case 0:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  		      break;
  		  case 1:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 2:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 3:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 4:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 5:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 6:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 7:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 8:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 9:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 10:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 11:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 12:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 13:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 14:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  case 15:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  }
  	  }
  	  else{
  		  switch(contador){
  		  case 0:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 1:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 1);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 2:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 1);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 3:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 1);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 0);
  			  break;
  		  case 4:
  			  HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, 0);
  			  HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, 0);
  			  HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, 0);
  			  HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, 1);
  			  break;
  		  }
  	  }

      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Led3_Pin|Led4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Led1_Pin|Led2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Bot1_Pin Bot2_Pin */
  GPIO_InitStruct.Pin = Bot1_Pin|Bot2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Led3_Pin Led4_Pin */
  GPIO_InitStruct.Pin = Led3_Pin|Led4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Bot3_Pin */
  GPIO_InitStruct.Pin = Bot3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Bot3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Led1_Pin Led2_Pin */
  GPIO_InitStruct.Pin = Led1_Pin|Led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
