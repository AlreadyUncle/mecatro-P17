#include "../../include/components/AX12_manager.h"


#define BAUDRATE                        1000000


AX12_manager::AX12_manager(string device_name) {
    // Initialize PortHandler instance
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(device_name);

    // Initialize PacketHandler instance
    // Set the protocol version
    // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(1.0); // 1.0 : protocol version

    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;                          // Dynamixel error
    uint16_t dxl_present_position = 0;              // Present position
}

int AX12_manager::init_connection() {
    // Open port
    if (portHandler->openPort()) {
        printf("Succeeded to open the port!\n");
    } else {
        printf("Failed to open the port!\n");
        return 0;
    }

    // Set port baudrate
    if (portHandler->setBaudRate(BAUDRATE)) {
        printf("Succeeded to change the baudrate!\n");
    } else {
        printf("Failed to change the baudrate!\n");
        return 0;
    }

    // Enable Dynamixel Torque
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, DXL_ID, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE,
                                                    &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    } else if (dxl_error != 0) {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    } else {
        printf("Dynamixel has been successfully connected \n");
    }
}