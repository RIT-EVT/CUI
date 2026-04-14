/**
 * This is a basic sample of using the UART module. The program provides a
 * basic echo functionality where the uart will write back whatever the user
 * enters.
 */

#include "core/dev/LED.hpp"

#include <core/io/UART.hpp>
#include <core/io/pin.hpp>
#include <core/manager.hpp>

namespace io = core::io;

constexpr io::Pin UART_TX = io::Pin::PA_9;
constexpr io::Pin UART_RX = io::Pin::PA_10;

constexpr io::Pin GPIO_LED1 = io::Pin::PB_5;
constexpr io::Pin GPIO_LED2 = io::Pin::PB_6;
constexpr io::Pin GPIO_LED3 = io::Pin::PB_7;

constexpr io::Pin CAN_RX = io::Pin::PB_12;
constexpr io::Pin CAN_TX = io::Pin::PB_13;

constexpr io::Pin SPI_SCK = io::Pin::PB_10;
constexpr io::Pin SPI_MOSI = io::Pin::PC_1;
constexpr io::Pin SPI_MISO = io::Pin::PC_2;

io::GPIO* devices[1];

int main() {
    // Initialize system
    core::platform::init();

    // Setup UART
    io::UART& uart = io::getUART<UART_TX, UART_RX>(9600);

    // Setup SPI
    io::SPI& spi = io::getSPI<SPI_SCK, SPI_MOSI, SPI_MOSI>(devices, 1);

    // Setup CAN
    io::CAN& can = io::getCAN<CAN_TX, CAN_RX>();

    // Setup GPIO LED's
    io::GPIO& gpio1 = io::getGPIO<GPIO_LED1>();
    core::dev::LED led1 = core::dev::LED(gpio1, core::dev::LED::ActiveState::LOW);

    io::GPIO& gpio2 = io::getGPIO<GPIO_LED2>();
    core::dev::LED led2 = core::dev::LED(gpio2, core::dev::LED::ActiveState::LOW);

    io::GPIO& gpio3 = io::getGPIO<GPIO_LED3>();
    core::dev::LED led3 = core::dev::LED(gpio3, core::dev::LED::ActiveState::LOW);

    // String to store user input
    char buf[100];

    while (1) {
        led1.toggle();
        led2.toggle();
        led3.toggle();

        // Read user input
        uart.printf("Enter message: ");
        uart.gets(buf, 100);
        uart.printf("\n\recho: %s\n\r", buf);
    }
}
