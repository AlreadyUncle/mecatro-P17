//
// Created by 魏士清 on 2019-01-22.
//

#include "AX12.h"


AX12::AX12(int ID, dynamixel::PortHandler *portHandler, dynamixel::PacketHandler *packetHandler) {
    this->ID = ID;
    // Initialize PortHandler instance
    // Set the port path
    // Get methods and members of PortHandlerLinux or PortHandlerWindows
    this->portHandler = portHandler;
    // Initialize PacketHandler instance
    // Set the protocol version
    // Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
    this->packetHandler = packetHandler;
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;                          // Dynamixel error

    // Open port
    if (portHandler->openPort()) {
        LOG_F(INFO, "[id %d] Succeeded to open the port!\n", this->ID);
    } else {
        LOG_F(ERROR, "[id %d] Failed to open the port!\n", this->ID);
    }

    // Set port baudrate
    if (portHandler->setBaudRate(BAUDRATE)) {
        LOG_F(INFO, "[id %d] Succeeded to change the baudrate!\n", this->ID);
    } else {
        LOG_F(ERROR, "[id %d] Failed to change the baudrate!\n", this->ID);
    }

    // Enable Dynamixel Torque
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_MX_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        LOG_F(ERROR, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
    } else if (dxl_error != 0) {
        LOG_F(ERROR, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
    } else {
        LOG_F(INFO, "[id %d] Dynamixel has been successfully connected \n", this->ID);
    }
}


void AX12::goToPositionJointMode(int pos) {                   // 0 <= pos <= 1023

    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;                          // Dynamixel error

    // Write goal position
    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_MX_GOAL_POSITION, pos, &dxl_error);

    if (dxl_comm_result != COMM_SUCCESS) {
        LOG_F(ERROR, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
    } else if (dxl_error != 0) {
        LOG_F(ERROR, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
    }
}

int AX12::getPosition() {
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;                          // Dynamixel error
    uint16_t dxl_present_position = 0;              // Present position
    dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, ID, ADDR_MX_PRESENT_POSITION, &dxl_present_position,
                                                   &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        LOG_F(ERROR, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
    } else if (dxl_error != 0) {
        LOG_F(ERROR, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
    }
    return dxl_present_position;


}

void AX12::setMode(AX12Mode mode) {
    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;

    if (mode == joint) {
        int CW = 0;
        int CCW = 1023;

        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_MX_CW_ANGLE_LIMIT, CW, &dxl_error);


        if (dxl_comm_result != COMM_SUCCESS) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
        }

        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_MX_CCW_ANGLE_LIMIT, CCW, &dxl_error);


        if (dxl_comm_result != COMM_SUCCESS) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
        }

    } else if (mode == wheel) {
        int CW = 0;
        int CCW = 0;

        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_MX_CW_ANGLE_LIMIT, CW, &dxl_error);


        if (dxl_comm_result != COMM_SUCCESS) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
        }

        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_MX_CCW_ANGLE_LIMIT, CCW, &dxl_error);


        if (dxl_comm_result != COMM_SUCCESS) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
        } else if (dxl_error != 0) {
            LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
        }

    }
}

void AX12::setSpeed(int speed) {                   // 0 <= pos <= 1023

    int dxl_comm_result = COMM_TX_FAIL;             // Communication result

    uint8_t dxl_error = 0;                          // Dynamixel error

    // Write goal moving speed

    dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_MX_MOVING_SPEED, speed, &dxl_error);


    if (dxl_comm_result != COMM_SUCCESS) {
        LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getTxRxResult(dxl_comm_result));
    } else if (dxl_error != 0) {
        LOG_F(INFO, "[id %d] %s\n", this->ID, packetHandler->getRxPacketError(dxl_error));
    }

}

