// STM32G071 IAR Startup file

#include "cmsis_compiler.h"
#include <stddef.h>

#if !defined(__ICCARM__)
  #error "Not IAR toolchain"
#endif

#ifdef __cplusplus
#define __EXTERN_C extern "C"
extern "C" {
#else
#define __EXTERN_C
#endif

#pragma segment="CSTACK"
#define __STACK_TOP  ((uint32_t)__sfe( "CSTACK" ))
void exit(){}
void __exit(){}
void abort(){}
void __cmain();

void Default_Handler() { for(;;); }

void NMI_Handler()                        __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()                  __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()                        __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()                     __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()                    __attribute__ ((weak, alias ("Default_Handler")));
void WWDG_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void PVD_IRQHandler()                     __attribute__ ((weak, alias ("Default_Handler")));
void RTC_TAMP_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void RCC_IRQHandler()                     __attribute__ ((weak, alias ("Default_Handler")));
void EXTI0_1_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void EXTI2_3_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void EXTI4_15_IRQHandler()                __attribute__ ((weak, alias ("Default_Handler")));
void UCPD1_2_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel2_3_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_COMP_IRQHandler()               __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler()     __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler()                 __attribute__ ((weak, alias ("Default_Handler")));
void TIM2_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void TIM3_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void TIM6_DAC_LPTIM1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void TIM7_LPTIM2_IRQHandler()             __attribute__ ((weak, alias ("Default_Handler")));
void TIM14_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void TIM15_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void TIM16_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void TIM17_IRQHandler()                   __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void SPI2_IRQHandler()                    __attribute__ ((weak, alias ("Default_Handler")));
void USART1_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void USART2_IRQHandler()                  __attribute__ ((weak, alias ("Default_Handler")));
void USART3_4_LPUART1_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void CEC_IRQHandler()                     __attribute__ ((weak, alias ("Default_Handler")));

typedef void(*intvec_elem)();

__EXTERN_C const intvec_elem __vector_table[] __VECTOR_TABLE_ATTRIBUTE =
{ (intvec_elem)__STACK_TOP, &__cmain,
  &NMI_Handler,
  &HardFault_Handler,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  &SVC_Handler,
  NULL, NULL,
  &PendSV_Handler,
  &SysTick_Handler,
  &WWDG_IRQHandler,
  &PVD_IRQHandler,
  &RTC_TAMP_IRQHandler,
  &FLASH_IRQHandler,
  &RCC_IRQHandler,
  &EXTI0_1_IRQHandler,
  &EXTI2_3_IRQHandler,
  &EXTI4_15_IRQHandler,
  &UCPD1_2_IRQHandler,
  &DMA1_Channel1_IRQHandler,
  &DMA1_Channel2_3_IRQHandler,
  &DMA1_Ch4_7_DMAMUX1_OVR_IRQHandler,
  &ADC1_COMP_IRQHandler,
  &TIM1_BRK_UP_TRG_COM_IRQHandler,
  &TIM1_CC_IRQHandler,
  &TIM2_IRQHandler,
  &TIM3_IRQHandler,
  &TIM6_DAC_LPTIM1_IRQHandler,
  &TIM7_LPTIM2_IRQHandler,
  &TIM14_IRQHandler,
  &TIM15_IRQHandler,
  &TIM16_IRQHandler,
  &TIM17_IRQHandler,
  &I2C1_IRQHandler,
  &I2C2_IRQHandler,
  &SPI1_IRQHandler,
  &SPI2_IRQHandler,
  &USART1_IRQHandler,
  &USART2_IRQHandler,
  &USART3_4_LPUART1_IRQHandler,
  &CEC_IRQHandler
};

#ifdef __cplusplus
}
#endif
