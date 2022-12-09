#include "debug_usart.h"

void board_console_init(void) {
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    /* enable USART clock */
    rcu_periph_clock_enable(RCU_UART4);

    /* connect port to USARTx_Tx */
    gpio_init(GPIOC, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
    /* connect port to USARTx_Rx */
    gpio_init(GPIOD, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

    /* USART configure */
    // UART Driver Version 1
    usart_deinit(UART4);
    usart_baudrate_set(UART4, 115200U);
    usart_receive_config(UART4, USART_RECEIVE_ENABLE);
    usart_transmit_config(UART4, USART_TRANSMIT_ENABLE);
    usart_enable(UART4);
}

int fputc(int ch, FILE *f) {
    usart_data_transmit(UART4, (uint8_t)ch);
    while (RESET == usart_flag_get(UART4, USART_FLAG_TBE)) {
        ;
    }
    return ch;
}
