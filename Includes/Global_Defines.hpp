#ifndef GLOBAL_DEFINES_HPP
#define GLOBAL_DEFINES_HPP

#include <string>

// Forward declare GPIO class
class GPIO;

#define QUEUE_SIZE 100
#define PACKET_SIZE 360
#define COMPRESSED_SIZE 360

#define GPIO1 506
#define GPIO2 507
#define GPIO_ON 1
#define GPIO_OFF 0
#define GPIO_OUT "OUT"
#define GPIO_IN "in"

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define GPIO_UNEXPORT_PATH "/sys/class/gpio/unexport"
#define GPIO_DIRECTION_PATH "/sys/class/gpio/gpio" + std::to_string(PinNumber) + "/direction"
#define GPIO_VALUE_PATH "/sys/class/gpio/gpio" + std::to_string(PinNumber) + "/value"

#define PACKETS_TO_FETCH 5
#define PROMISC 1
#define READ_TIMEOUT 1000
#define LOOP_COUNT -1

#define SOURCE_IP "192.168.1.1"
#define SOURCE_PORT 1234
#define SOURCE_DEVICE "eth0"

#define DESTINATION_IP "192.168.1.2"
#define DESTINATION_PORT 1234
#define DESTINATION_DEVICE "eth1"

#define UDP_HEADER_SIZE 8
#define ETH_FILTER "udp and src host 192.168.1.1"

#define ETH_DEVICE_COUNT 2

extern GPIO LinkStatusLed;
extern GPIO PacketTrafficStatusLed;
extern bool PacketRecived;

#endif // GLOBAL_DEFINES_HPP
