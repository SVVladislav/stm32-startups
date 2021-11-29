// STM32G071 Startup file
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
  void exit(){}
  void __exit(){}
  void abort(){}
  void __cmain();
#endif

#ifdef __KEIL_CODE__
//------------------------------
// Keil startup code
//------------------------------
  void __main();
  void SystemInit();
  void exit() __attribute__ ((weak, alias ("Default_Handler")));
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
  extern void (*__preinit_array_start[]) (void) __attribute__((weak));
  extern void (*__preinit_array_end[]) (void) __attribute__((weak));
  extern void (*__init_array_start[]) (void) __attribute__((weak));
  extern void (*__init_array_end[]) (void) __attribute__((weak));
  extern void (*__fini_array_start[]) (void) __attribute__((weak));
  extern void (*__fini_array_end[]) (void) __attribute__((weak));

  void __attribute__((naked, noreturn)) Reset_Handler()
  {
    #ifdef __DEBUG_SRAM__
      __set_MSP((uint32_t)&_estack);
    #endif

    SystemInit();

    extern uint32_t _sidata[], _sdata[], _edata[];
    for(volatile uint32_t *pSrc=_sidata, *pDst=_sdata; pDst!=_edata; *pDst++=*pSrc++);

    extern uint32_t _sbss[], _ebss[];
    for(volatile uint32_t *pDst=_sbss; pDst!=_ebss; *pDst++=0); // Zero -> BSS

#if (1)
    // Use with the "-nostartfiles" linker option instead __libc_init_array();
    // Iterate over all the preinit/init routines (mainly static constructors).
    for(void(**fConstr)() = __preinit_array_start; fConstr < __preinit_array_end; (*fConstr++)());
    for(void(**fConstr)() = __init_array_start;    fConstr < __init_array_end;    (*fConstr++)());
#else
   __libc_init_array(); // Use with libc start files
#endif

    main();
  }
#endif // __GCC_CODE__


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
{ (intvec_elem)__STACK_TOP, &__Reset_Handler,
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
