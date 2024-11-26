#pragma once
#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#define QUEUE_SIZE 10
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
#define READ_TIMOUT 1000 // If no packets recived in 1000ms
#define LOOP_COUNT -1

#define RECIVER_IP "192.168.1.1"
#define RECIVER_DEVICE "eth0"
#define UDP_HEADER_SIZE 8
#define ETH_FILTER "udp and src host 192.168.1.1"

#define DESTINATION_IP "192.168.1.2"
#define DESTINATION_PORT 5353 //whatever
#define DESTINATION_DEVICE "eth1"

#define SOCKET_PROTOCTOL 0

#define SENDTO_FLAG 0


#endif