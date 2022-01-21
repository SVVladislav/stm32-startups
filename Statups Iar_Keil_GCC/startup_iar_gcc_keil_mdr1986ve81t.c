// MDR1986VE8xT Startup file
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

void NMI_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void HardFault_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void MemManage_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void BusFault_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void UsageFault_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void SVC_Handler()               __attribute__ ((weak, alias ("Default_Handler")));
void PendSV_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void SysTick_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void FT_IF0_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void FT_IF1_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void FT_IF2_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void FT_IF3_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void CLK_IF_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void PVD_IF_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void RTC_IF_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void BKP_IF_Handler()            __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR0_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR1_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR2_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR3_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR4_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR5_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR6_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void EXT_INTERROR7_Handler()     __attribute__ ((weak, alias ("Default_Handler")));
void DMA_ERR_Handler()           __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE0_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE1_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE2_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE3_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE4_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE5_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE6_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE7_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE8_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE9_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE10_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE11_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE12_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE13_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE14_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE15_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE16_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE17_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE18_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE19_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE20_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE21_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE22_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE23_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE24_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE25_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE26_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE27_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE28_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE29_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE30_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void DMA_DONE31_Handler()        __attribute__ ((weak, alias ("Default_Handler")));
void IRQ_PORTA_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void IRQ_PORTB_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void IRQ_PORTC_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void IRQ_PORTD_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void IRQ_PORTE_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void INT_ETH0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_SPW0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_TMR0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_TMR1_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_TMR2_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_TMR3_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_CAN0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_SSP0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_UART0_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void INT_UART1_Handler()         __attribute__ ((weak, alias ("Default_Handler")));
void INT_RX_ARC0_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void INT_TX_ARC0_Handler()       __attribute__ ((weak, alias ("Default_Handler")));
void INT_MIL0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_MIL1_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_ADC0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_ADC1_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_DAC0_Handler()          __attribute__ ((weak, alias ("Default_Handler")));
void INT_DAC1_Handler()          __attribute__ ((weak, alias ("Default_Handler")));

typedef union { void(*__fun)(); void *__ptr; } intvec_elem;

__EXTERN_C const intvec_elem __vector_table[] __attribute__ ((section (__VECTORS_SECTION__), used)) =
{
  {.__ptr = __STACK_TOP},
  &__Reset_Handler,
  &NMI_Handler,
  &HardFault_Handler,
  &MemManage_Handler,
  &BusFault_Handler,
  &UsageFault_Handler,
  NULL, NULL, NULL, NULL,
  &SVC_Handler,
  NULL, NULL,
  &PendSV_Handler,
  &SysTick_Handler,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  &FT_IF0_Handler,
  &FT_IF1_Handler,
  &FT_IF2_Handler,
  &FT_IF3_Handler,
  &CLK_IF_Handler,
  &PVD_IF_Handler,
  &RTC_IF_Handler,
  &BKP_IF_Handler,
  &EXT_INTERROR0_Handler,
  &EXT_INTERROR1_Handler,
  &EXT_INTERROR2_Handler,
  &EXT_INTERROR3_Handler,
  &EXT_INTERROR4_Handler,
  &EXT_INTERROR5_Handler,
  &EXT_INTERROR6_Handler,
  &EXT_INTERROR7_Handler,
  NULL, NULL,
  &DMA_ERR_Handler,
  &DMA_DONE0_Handler,
  &DMA_DONE1_Handler,
  &DMA_DONE2_Handler,
  &DMA_DONE3_Handler,
  &DMA_DONE4_Handler,
  &DMA_DONE5_Handler,
  &DMA_DONE6_Handler,
  &DMA_DONE7_Handler,
  &DMA_DONE8_Handler,
  &DMA_DONE9_Handler,
  &DMA_DONE10_Handler,
  &DMA_DONE11_Handler,
  &DMA_DONE12_Handler,
  &DMA_DONE13_Handler,
  &DMA_DONE14_Handler,
  &DMA_DONE15_Handler,
  &DMA_DONE16_Handler,
  &DMA_DONE17_Handler,
  &DMA_DONE18_Handler,
  &DMA_DONE19_Handler,
  &DMA_DONE20_Handler,
  &DMA_DONE21_Handler,
  &DMA_DONE22_Handler,
  &DMA_DONE23_Handler,
  &DMA_DONE24_Handler,
  &DMA_DONE25_Handler,
  &DMA_DONE26_Handler,
  &DMA_DONE27_Handler,
  &DMA_DONE28_Handler,
  &DMA_DONE29_Handler,
  &DMA_DONE30_Handler,
  &DMA_DONE31_Handler,
  &IRQ_PORTA_Handler,
  &IRQ_PORTB_Handler,
  &IRQ_PORTC_Handler,
  &IRQ_PORTD_Handler,
  &IRQ_PORTE_Handler,
  NULL,
  &INT_ETH0_Handler,
  NULL,
  &INT_SPW0_Handler,
  NULL,
  &INT_TMR0_Handler,
  &INT_TMR1_Handler,
  &INT_TMR2_Handler,
  &INT_TMR3_Handler,
  NULL, NULL,
  &INT_CAN0_Handler,
  NULL, NULL, NULL, NULL,
  &INT_SSP0_Handler,
  NULL, NULL, NULL,
  &INT_UART0_Handler,
  &INT_UART1_Handler,
  NULL, NULL, NULL,
  &INT_RX_ARC0_Handler,
  &INT_TX_ARC0_Handler,
  NULL, NULL,
  &INT_MIL0_Handler,
  &INT_MIL1_Handler,
  &INT_ADC0_Handler,
  &INT_ADC1_Handler,
  &INT_DAC0_Handler,
  &INT_DAC1_Handler
};

#ifdef __cplusplus
}
#endif
