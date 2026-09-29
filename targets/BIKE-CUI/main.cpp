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
namespace dev = core::dev;

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

constexpr io::Pin BTN_UP = io::Pin::PC_13;
constexpr io::Pin BTN_DOWN = io::Pin::PC_14;
constexpr io::Pin BTN_LEFT = io::Pin::PH_1;
constexpr io::Pin BTN_RIGHT = io::Pin::PC_15;
constexpr io::Pin BTN_CENTER = io::Pin::PH_0;

constexpr io::Pin ENC_A = io::Pin::PA_4; //clockwise leading active low
constexpr io::Pin ENC_B = io::Pin::PA_5; //counter clockwise leading active low
constexpr io::Pin ENC_1 = io::Pin::PA_6; //push button active low

constexpr io::Pin USB_DN = io::Pin::PB_14;
constexpr io::Pin USB_DP = io::Pin::PB_15;

constexpr io::Pin SDIO_D0 = io::Pin::PC_8;
constexpr io::Pin SDIO_D1 = io::Pin::PB_0;
constexpr io::Pin SDIO_D2 = io::Pin::PB_1;
constexpr io::Pin SDIO_D3 = io::Pin::PC_11;
constexpr io::Pin SDIO_CMD = io::Pin::PD_2;
constexpr io::Pin SDIO_CLK = io::Pin::PB_2;

constexpr io::Pin CHARGE_STATUS = io::Pin::PC_5;
constexpr io::Pin BAL_N = io::Pin::PC_6; //need to drive high when PACK+ < 6V
constexpr io::Pin PACK_F = io::Pin::PC_4; //ADC for estimating battery SOC using lookup table, voltage read x 2.65 = actual battery voltage

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
    dev::LED led1 = dev::LED(gpio1, dev::LED::ActiveState::LOW);

    io::GPIO& gpio2 = io::getGPIO<GPIO_LED2>();
    dev::LED led2 = dev::LED(gpio2, dev::LED::ActiveState::LOW);

    io::GPIO& gpio3 = io::getGPIO<GPIO_LED3>();
    dev::LED led3 = dev::LED(gpio3, dev::LED::ActiveState::LOW);

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
