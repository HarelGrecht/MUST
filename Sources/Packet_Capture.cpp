#include "../Includes/Packet_Capture.hpp"
#include "../Includes/Global_Defines.hpp"

#include <cstring>
#include <iostream>
#include <thread>
#include <vector>



/*
if MOCK_UP is defined:
    ifndef blocks are ignored
    ifdef blocks are include
if MOCK_IP is not defined:
    ifndef blocks are included
    ifdef blocks are ignored
*/
Queue PacketCapture::ReciveQueue;

PacketCapture::PacketCapture(const std::string& device, std::string IpAddress) : Device(device), IpAddress(IpAddress) {
#ifndef MOCK_UP
    SetIPAddress(Device, IpAddress);
#endif
}

PacketCapture::~PacketCapture() {
#ifndef MOCK_UP
    if (NetworkDescriptor != nullptr)
        pcap_close(NetworkDescriptor);
#endif
}

#ifdef MOCK_UP
// Mock-up function to inject fake packets
void PacketCapture::InjectFakePackets() {
    std::cout << "MOCK_UP: Injecting fake packets..." << std::endl;
    while (true) {  // Simulate continuous packet reception
        uint8_t fakePacket[PACKET_SIZE] = {0};

        // Fill the packet with dummy data (example: incrementing byte values)
        for (size_t i = 0; i < PACKET_SIZE; ++i) {
            fakePacket[i] = i % 256;
        }

        // Enqueue the fake packet into the receiving queue
        if (ReciveQueue.enqueue(fakePacket, PACKET_SIZE)) {
            std::cout << "MOCK_UP: Injected fake packet of size " << PACKET_SIZE << " bytes into the queue." << std::endl;
        } else {
            std::cerr << "MOCK_UP: Failed to enqueue fake packet. Queue might be full." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate packet arrival every 100 ms
    }
}
#endif

bool PacketCapture::StartCapture(const std::string& FilterString) {
#ifdef MOCK_UP
    // Start a thread to inject fake packets
    std::thread injectorThread(&PacketCapture::InjectFakePackets, this);
    injectorThread.detach();  // Let the thread run in the background
    return true;
#else
    if (!OpenDevice()) {
        return false;
    }
    if (!SetFilter(FilterString)) {
        return false;
    }
    std::cout << "Starting capturing packets on device " << Device << std::endl;
    if (pcap_loop(NetworkDescriptor, 0, RecivePacketHandler, reinterpret_cast<uint8_t*>(this)) < 0) {
        std::cerr << "Error capturing packets: " << pcap_geterr(NetworkDescriptor) << std::endl;
        return false;
    }
    return true;
#endif
}

#ifndef MOCK_UP
// Original packet handler for real mode
void PacketCapture::RecivePacketHandler(uint8_t* GlobalData, const struct pcap_pkthdr* PacketHeader, const uint8_t* PacketData) {
    PacketRecived = true;
    std::cout << "Packet captured with length: " << PacketHeader->len << std::endl;
    const uint8_t* PayloadData = PacketData + UDP_HEADER_LENGTH;
    const size_t PayloadLen = PacketHeader->len - UDP_HEADER_LENGTH;
    if (ReciveQueue.enqueue(PayloadData, PayloadLen)) {
        std::cout << "Packet added to queue, length: " << PayloadLen << " bytes." << std::endl;
    } else {
        std::cerr << "Failed to enqueue packet. Queue might be full." << std::endl;
    }
}
#endif
