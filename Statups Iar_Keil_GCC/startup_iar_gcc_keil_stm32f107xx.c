// STM32F107 Startup file
// IAR, GCC, Keil compatible

#include "cmsis_compiler.h"
#include <stddef.h>

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION>=6100100)
#define __KEIL_CODE__
#elif defined(__GNUC__)
#define __GCC_CODE__
#elif defined(__ICCARM__)
#define __IAR_CODE__
#elif defined( __CC_ARM ) || defined(__MICROLIB)
#error "ARMCC v5 and MICROLIB not supported"
#else
#error "Can't detect compiler"
#endif

#ifdef __cplusplus
#define __EXTERN_C extern "C"
extern "C" {
#else
#define __EXTERN_C
#endif

#ifdef __IAR_CODE__
  //------------------------------
  // IAR startup code
  //------------------------------
#define __Reset_Handler __cmain
#pragma segment="CSTACK"
#define __STACK_TOP  ((uint32_t)__sfe( "CSTACK" ))
  void exit() {}
  void __cmain();
#endif

#ifdef __KEIL_CODE__
  //------------------------------
  // Keil startup code
  //------------------------------
  void __main();
  void SystemInit();
  void exit() __attribute__((weak, alias("Default_Handler")));
#define __Reset_Handler Reset_Handler
#define __STACK_TOP (void *)&Image$$ARM_LIB_STACK$$ZI$$Limit
  extern int Image$$ARM_LIB_STACK$$ZI$$Limit;

  void Reset_Handler()
  {
    SystemInit();
    __main();
  }
#endif // __KEIL_CODE__

#ifdef __GCC_CODE__
  //------------------------------
  // GCC Newlib startup code
  //------------------------------
#define __Reset_Handler Reset_Handler
#define __STACK_TOP  &_estack
  void SystemInit();
  void __libc_init_array();
  int main();

  // These magic symbols are provided by the linker.
  extern void *_estack;
  extern void(*__preinit_array_start[])(void) __attribute__((weak));
  extern void(*__preinit_array_end[])(void) __attribute__((weak));
  extern void(*__init_array_start[])(void) __attribute__((weak));
  extern void(*__init_array_end[])(void) __attribute__((weak));
  extern void(*__fini_array_start[])(void) __attribute__((weak));
  extern void(*__fini_array_end[])(void) __attribute__((weak));

  void __attribute__((naked, noreturn)) Reset_Handler()
  {
#ifdef __DEBUG_SRAM__
    __set_MSP((uint32_t)&_estack);
#endif

    SystemInit();

#ifndef __DEBUG_SRAM__
    extern uint32_t _sidata[], _sdata[], _edata[];
    for (volatile uint32_t *pSrc = _sidata, *pDst = _sdata; pDst != _edata; *pDst ++= *pSrc++) ;
#endif

    extern uint32_t _sbss[], _ebss[];
    for (volatile uint32_t *pDst = _sbss; pDst != _ebss; *pDst ++= 0) ; // Zero -> BSS

#if (1)
    // Use with the "-nostartfiles" linker option instead __libc_init_array();
    // Iterate over all the preinit/init routines (mainly static constructors).
    for (void(**fConstr)() = __preinit_array_start; fConstr < __preinit_array_end; (*fConstr++)()) ;
    for (void(**fConstr)() = __init_array_start; fConstr < __init_array_end; (*fConstr++)()) ;
#else
    __libc_init_array(); // Use with libc start files
#endif

    main();
  }
#endif // __GCC_CODE__

void Default_Handler() { for(;;); }

void NMI_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void DebugMon_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void WWDG_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void PVD_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void TAMPER_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void RTC_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void FLASH_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void RCC_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void EXTI0_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void EXTI1_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void EXTI2_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void EXTI3_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void EXTI4_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel2_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel3_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel4_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel5_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel6_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA1_Channel7_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void ADC1_2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_TX_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_RX0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_RX1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void CAN1_SCE_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void EXTI9_5_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_BRK_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_UP_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_IRQHandler()   __attribute__ ((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void TIM2_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIM3_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIM4_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_EV_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void I2C2_ER_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void SPI2_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void USART1_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void USART2_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void USART3_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void RTC_Alarm_IRQHandler()      __attribute__ ((weak, alias ("Default_Handler")));
void OTG_FS_WKUP_IRQHandler()    __attribute__ ((weak, alias ("Default_Handler")));
void TIM5_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void SPI3_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void UART4_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void UART5_IRQHandler()          __attribute__ ((weak, alias ("Default_Handler")));
void TIM6_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void TIM7_IRQHandler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Channel1_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Channel2_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Channel3_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Channel4_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void DMA2_Channel5_IRQHandler()  __attribute__ ((weak, alias ("Default_Handler")));
void ETH_IRQHandler()            __attribute__ ((weak, alias ("Default_Handler")));
void ETH_WKUP_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void CAN2_TX_IRQHandler()        __attribute__ ((weak, alias ("Default_Handler")));
void CAN2_RX0_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void CAN2_RX1_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void CAN2_SCE_IRQHandler()       __attribute__ ((weak, alias ("Default_Handler")));
void OTG_FS_IRQHandler()         __attribute__ ((weak, alias ("Default_Handler")));

typedef void(*intvec_elem)();

__EXTERN_C const intvec_elem __vector_table[] __VECTOR_TABLE_ATTRIBUTE =
{ (intvec_elem)__STACK_TOP, &__Reset_Handler,
  &NMI_Handler,
  &HardFault_Handler,
  &MemManage_Handler,
  &BusFault_Handler,
  &UsageFault_Handler,
  NULL, NULL, NULL, NULL,
  &SVC_Handler,
  &DebugMon_Handler,
  NULL,
  &PendSV_Handler,
  &SysTick_Handler,
  &WWDG_IRQHandler,
  &PVD_IRQHandler,
  &TAMPER_IRQHandler,
  &RTC_IRQHandler,
  &FLASH_IRQHandler,
  &RCC_IRQHandler,
  &EXTI0_IRQHandler,
  &EXTI1_IRQHandler,
  &EXTI2_IRQHandler,
  &EXTI3_IRQHandler,
  &EXTI4_IRQHandler,
  &DMA1_Channel1_IRQHandler,
  &DMA1_Channel2_IRQHandler,
  &DMA1_Channel3_IRQHandler,
  &DMA1_Channel4_IRQHandler,
  &DMA1_Channel5_IRQHandler,
  &DMA1_Channel6_IRQHandler,
  &DMA1_Channel7_IRQHandler,
  &ADC1_2_IRQHandler,
  &CAN1_TX_IRQHandler,
  &CAN1_RX0_IRQHandler,
  &CAN1_RX1_IRQHandler,
  &CAN1_SCE_IRQHandler,
  &EXTI9_5_IRQHandler,
  &TIM1_BRK_IRQHandler,
  &TIM1_UP_IRQHandler,
  &TIM1_TRG_COM_IRQHandler,
  &TIM1_CC_IRQHandler,
  &TIM2_IRQHandler,
  &TIM3_IRQHandler,
  &TIM4_IRQHandler,
  &I2C1_EV_IRQHandler,
  &I2C1_ER_IRQHandler,
  &I2C2_EV_IRQHandler,
  &I2C2_ER_IRQHandler,
  &SPI1_IRQHandler,
  &SPI2_IRQHandler,
  &USART1_IRQHandler,
  &USART2_IRQHandler,
  &USART3_IRQHandler,
  &EXTI15_10_IRQHandler,
  &RTC_Alarm_IRQHandler,
  &OTG_FS_WKUP_IRQHandler,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL,
  &TIM5_IRQHandler,
  &SPI3_IRQHandler,
  &UART4_IRQHandler,
  &UART5_IRQHandler,
  &TIM6_IRQHandler,
  &TIM7_IRQHandler,
  &DMA2_Channel1_IRQHandler,
  &DMA2_Channel2_IRQHandler,
  &DMA2_Channel3_IRQHandler,
  &DMA2_Channel4_IRQHandler,
  &DMA2_Channel5_IRQHandler,
  &ETH_IRQHandler,
  &ETH_WKUP_IRQHandler,
  &CAN2_TX_IRQHandler,
  &CAN2_RX0_IRQHandler,
  &CAN2_RX1_IRQHandler,
  &CAN2_SCE_IRQHandler,
  &OTG_FS_IRQHandler,
#if 0
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL,
  (void *)0xF1E0F85F // BootRAM
#endif
};

#ifdef __cplusplus
}
#endif
