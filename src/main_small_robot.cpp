#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_cpp/loggers/bt_file_logger.h"
#include "behaviortree_cpp/loggers/bt_minitrace_logger.h"
#include "dynamixel_sdk.h"
#include <wiringPi.h>
#include "loguru.hpp"

#include "components/AX12.h"
#include "components/Kangaroo.h"
#include "components/LCD.h"
#include "components/SerialPort.h"
#include "components/UltrasonicSensor.h"

#include "strategy/Nodes.h"
#include "components/JackSmallRobot.h"

using namespace std;
using namespace BT;


int main(int argc, char *argv[]) {
    // -----------------------
    // Initialize logger
    loguru::init(argc, argv);
    loguru::add_file("../log/everything.log", loguru::Append, loguru::Verbosity_MAX);
    loguru::add_file("../log/info.log", loguru::Append, loguru::Verbosity_INFO);


    // -----------------------
    // Initialize robot components
    // Kangaroo
    Kangaroo kangaroo(SERIAL_PORT_KANGAROO_SR);
    if (kangaroo.isOperational())
        LOG_F(INFO, "Kangaroo is operational");
    else
        LOG_F(ERROR, "Kangaroo is not operational !");

    // AX-12
    dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

    AX12 axOpenPince(AX_ID_SR_OPEN_PINCE, portHandler, packetHandler);

    // Other
    UltrasonicSensor frontSensor(FRONT_SENSOR_TRIGGER_PIN_SR, FRONT_SENSOR_ECHO_PIN_SR);
    UltrasonicSensor backSensor(BACK_SENSOR_TRIGGER_PIN_SR, BACK_SENSOR_ECHO_PIN_SR);
    JackSmallRobot jack;

    // -----------------------
    // Create the behavior tree

    // We use the BehaviorTreeFactory to register our custom nodes
    BehaviorTreeFactory factory;
    // Note: the name used to register should be the same used in the XML.
    using namespace Robot;

    // A node builder is nothing more than a function pointer to create a
    // std::unique_ptr<TreeNode>.
    // Using lambdas or std::bind, we can easily "inject" additional arguments.

    // Kangaroo
    NodeBuilder builderMoveAhead;
    builderMoveAhead = [&](const std::string &name, const NodeConfiguration &config) {
        return std::make_unique<MoveAhead>(name, config, frontSensor, frontSensor, backSensor, backSensor, kangaroo, false);
    };
    NodeBuilder builderTurn;
    builderTurn = [&](const std::string &name, const NodeConfiguration &config) {
        return std::make_unique<Turn>(name, config, kangaroo, false);
    };
    factory.registerBuilder<MoveAhead>("MoveAhead", builderMoveAhead);
    factory.registerBuilder<Turn>("Turn", builderTurn);

    // AX-12
    NodeBuilder builderOpenPince = [&](const std::string &name, const NodeConfiguration &config) {
        return std::make_unique<MoveAX12Joint>(name, config, axOpenPince);
    };
    factory.registerBuilder<MoveAX12Joint>("OpenPince", builderOpenPince);

    // Other
    factory.registerNodeType<Wait>("Wait");

    // Trees are created at deployment-time (i.e. at run-time, but only
    // once at the beginning).

    // IMPORTANT: when the object "tree" goes out of scope, all the
    // TreeNodes are destroyed
    auto tree = factory.createTreeFromFile(
            "/home/pi/mecatro_P17/src/strategy/tree_homologation_small_robot_purple.xml"); // requires absolute paths

    // This logger saves state changes on file
    MinitraceLogger logger_minitrace(tree, "/home/pi/mecatro_P17/log/bt_trace.json");
    printTreeRecursively(tree.root_node);


    jack.waitToRemove();

    // -----------------------
    // Turn on the experiment
    SerialPort xBee;
    if (xBee.open(SERIAL_PORT_XBEE, 9600) != -1) {
        LOG_F(INFO, "XBee Serial Port opened");
        for(int i=0;i<1000;i++){
            xBee.puts("!@#$%^&*()");
            LOG_F(INFO, "String sent to Xbee");
        }
    } else
        LOG_F(ERROR, "Could not open Xbee serial port");

/*
    // -----------------------
    // Execute the behavior tree

    while (tree.root_node->executeTick() == NodeStatus::RUNNING) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
*/
    return 0;
}