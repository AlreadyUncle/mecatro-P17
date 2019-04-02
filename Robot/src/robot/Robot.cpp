//
// Created by Alexandre Thomas on 2019-03-05.
//

#include "Robot.h"

#define PORT_NAME_KANGAROO              "/dev/serial0"      // Port address for Kangaroo
#define PORT_NAME_DXL                   "/dev/ttyACM0"      // Port adress for dynamixel devices
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel



bool Robot::goTo(int x, int y, int speed, int angle) {
    
}

bool Robot::stop(bool verbose){return m_kangaroo.forwardNB(0,0,verbose);}

int Robot::getX() {
    return 0;
}

int Robot::getY() {
    return 0;
}

int Robot::getAngle() {
    return 0;
}

Robot::Robot(int n_ax12) {
    srand(time(0));
    // initialize all devices
    m_portHandler = dynamixel::PortHandler::getPortHandler(PORT_NAME_DXL);
    m_packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
    m_ax_servos = new AX12[n_ax12];
    for(int id=0;id<n_ax12;id++){
        m_ax_servos[id] = AX12(id, m_portHandler, m_packetHandler);
        m_ax_servos[id].setMode(joint);
    }

    m_kangaroo = Ckangaroo(PORT_NAME_KANGAROO);
    m_sensor = US_sensor();
    m_screen = LCD();
    if(m_kangaroo.isOperationnal()){
        cout<<"Kangaroo operationnal"<<endl;
    }
}

