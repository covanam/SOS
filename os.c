#include "os.h"
#include "gpio.h"
#include <stdint.h>

struct SYST_t {
    volatile uint32_t CSR;
    volatile uint32_t RVR;
    volatile uint32_t CVR;
    volatile uint32_t CALIB;
};

static struct SYST_t *const SYST = (struct SYST_t *)(0xE000E010);

void SVC_Handler(void) {
    SYST->RVR = 16000u;
    SYST->CVR = 16000u;
    SYST->CSR = 7u;
}

void SysTick_Handler(void) {
    static uint32_t millisecond_count = 0;
    millisecond_count++;
    if (millisecond_count == 1000u) {
        millisecond_count = 0u;
        GPIOD->ODR ^= (1u << 12u) | (1u << 13u) | (1u << 14u) | (1u << 15u);
    }
}

void start_os(void) {
    __asm__("svc #0");
    while (1) {
        __asm__("wfe");
    }
}