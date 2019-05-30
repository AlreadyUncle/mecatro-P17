//
// Created by Alexandre Thomas on 2019-05-03.
//

#ifndef MECATRO_P17_NODES_H
#define MECATRO_P17_NODES_H

#include "thread"
#include "behaviortree_cpp/behavior_tree.h"
#include "loguru.hpp"
#include "../components/UltrasonicSensor.h"
#include "../components/Kangaroo.h"
#include "../components/AX12.h"
#include "../components/LCD.h"
#include "../components/RelayModule.h"
#include "../components/Encoder.h"

#define SERIAL_PORT_KANGAROO_BR         "/dev/ttyUSB0"
#define SERIAL_PORT_XBEE                "/dev/ttyUSB2"
#define SERIAL_PORT_ECRAN_BR            "/dev/serial0"
#define SERIAL_PORT_KANGAROO_SR         "/dev/ttyUSB0"

// Kangaroo
#define UNITS_PER_MM_BR                 5.669
#define UNITS_PER_MM_SR                 59.22
#define UNITS_PER_DEGREE_BR             13.89
#define UNITS_PER_DEGREE_SR             134.389
#define KANGAROO_SPEED_BR               500
#define KANGAROO_ROTATION_SPEED_BR      500
#define KANGAROO_SPEED_SR               5000
#define KANGAROO_ROTATION_SPEED_SR      5000

// AX-12
#define DXL_WHEEL_SPEED                 500
#define DXL_JOINT_SPEED                 500       // 1 to 1023 (max speed), 0 is for max speed
#define AX_ID_BR_PUSH_RIGHT_ATOM        6       // BR stands for big robot
#define AX_ID_BR_PUSH_LEFT_ATOM         2
#define AX_ID_BR_MOVE_ARM_SIDE          3
#define AX_ID_BR_MOVE_ARM_FRONT         4
#define AX_ID_BR_TURN_ARM               5
#define AX_ID_SR_OPEN_PINCE             3

// Other Pins definition
#define SENSOR_OBSTACLE_THRESHOLD_SR           240     // distance (in mm) under which obstacles are considered
#define SENSOR_OBSTACLE_THRESHOLD_BR           20     // distance (in mm) under which obstacles are considered
#define FRONT_SENSOR_TRIGGER_PIN_SR         4
#define FRONT_SENSOR_ECHO_PIN_SR            5
#define BACK_SENSOR_TRIGGER_PIN_SR          0
#define BACK_SENSOR_ECHO_PIN_SR             2
#define FRONT_SENSOR_LEFT_TRIGGER_PIN_BR    5
#define FRONT_SENSOR_LEFT_ECHO_PIN_BR       4
#define FRONT_SENSOR_RIGHT_TRIGGER_PIN_BR   26
#define FRONT_SENSOR_RIGHT_ECHO_PIN_BR      27
#define BACK_SENSOR_LEFT_TRIGGER_PIN_BR     3
#define BACK_SENSOR_LEFT_ECHO_PIN_BR        7
#define BACK_SENSOR_RIGHT_TRIGGER_PIN_BR    0
#define BACK_SENSOR_RIGHT_ECHO_PIN_BR       2
#define PUMP_RELAY_MODULE_PIN               21
#define BARREL_RELAY_MODULE_PIN             22

using namespace BT;

namespace Robot {

    /**
     * Move (forward or backward, depending on the signe of `distance`) a certain distance, while checking the obstacles.
     * If there are any obstacles, stop and wait.
     * Return RUNNING until the movement is completed, then return SUCCESS.
     */
    class MoveAhead : public CoroActionNode {
    public:
        MoveAhead(const std::string &name, const NodeConfiguration &config, UltrasonicSensor &frontSensorLeft,
                  UltrasonicSensor &frontSensorRight, UltrasonicSensor &backSensorLeft,
                  UltrasonicSensor &backSensorRight, Kangaroo &kangaroo, bool bigRobot) :
                CoroActionNode(name, config),
                _frontSensorLeft(frontSensorLeft),
                _frontSensorRight(frontSensorRight),
                _backSensorLeft(backSensorLeft),
                _backSensorRight(backSensorRight),
                _kangaroo(kangaroo),
                _bigRobot(bigRobot) {}

        NodeStatus tick() override;

        void cleanup(bool halted);

        void halt() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {
                    InputPort<int>("distance")
            };
        }

    private:
        bool _bigRobot;
        bool isMoving = false;
        UltrasonicSensor &_frontSensorLeft;
        UltrasonicSensor &_frontSensorRight;
        UltrasonicSensor &_backSensorLeft;
        UltrasonicSensor &_backSensorRight;
        Kangaroo &_kangaroo;
    };

    /**
     * Turn a certain angle
     */
    class Turn : public CoroActionNode {
    public:
        Turn(const std::string &name, const NodeConfiguration &config,
             Kangaroo &kangaroo, bool bigRobot) :
                CoroActionNode(name, config),
                _kangaroo(kangaroo),
                _bigRobot(bigRobot) {}

        NodeStatus tick() override;

        void cleanup(bool halted);

        void halt() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {
                    InputPort<int>("angle")
            };
        };


    private:
        bool _bigRobot;
        Kangaroo &_kangaroo;
    };

    /**
     * Activate an AX12 to make it move to position `pos`.
     */
    class MoveAX12Joint : public CoroActionNode {
    public:
        MoveAX12Joint(const std::string &name, const NodeConfiguration &config, AX12 &ax) :
                CoroActionNode(name, config),
                _ax(ax) {}

        NodeStatus tick() override;

        void cleanup(bool halted);

        void halt() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {
                    InputPort<int>("pos"),
            };
        }

    private:
        AX12 _ax;
    };

    /**
     * Activate an AX12 in wheel mode during a certain duration, proportional to `distance`.
     * The rotation direction (CW or CCW) is determined by the sign of `distance`
     * Return RUNNING until the movement is completed, then return SUCCESS.
     */
    class MoveAX12Wheel : public CoroActionNode {
    public:
        MoveAX12Wheel(const std::string &name, const NodeConfiguration &config, AX12 &ax) :
                CoroActionNode(name, config),
                _ax(ax) {}

        NodeStatus tick() override;

        void cleanup(bool halted);

        void halt() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {
                    InputPort<int>("distance"),
            };
        }

    private:
        AX12 _ax;
    };

    class ActivateRelayModule : public SyncActionNode {
    public:
        ActivateRelayModule(const std::string &name, const NodeConfiguration &config,
                            RelayModule &relayModule) :
                SyncActionNode(name, config),
                _relayModule(relayModule) {}

        NodeStatus tick() override;

    private:
        RelayModule &_relayModule;
    };

    class DeactivateRelayModule : public SyncActionNode {
    public:
        DeactivateRelayModule(const std::string &name, const NodeConfiguration &config,
                              RelayModule &relayModule) :
                SyncActionNode(name, config),
                _relayModule(relayModule) {}

        NodeStatus tick() override;

    private:
        RelayModule &_relayModule;
    };

    /**
     * Update the internal score estimation, and print it to the LCD screen.
     */
    class UpdateScore : public SyncActionNode {
    public:
        UpdateScore(const std::string &name, const NodeConfiguration &config, LCD &lcd) :
                SyncActionNode(name, config),
                _lcd(lcd) {}

        NodeStatus tick() override;

        static PortsList providedPorts() {
            InputPort<int>("pointsEarned");
        }

    private:
        int currentScore = 0;
        LCD &_lcd;
    };

    /**
     * Check the global counter to see if the barrel has reached goalPosition
     * Returns SUCCESS if move is finished, FAILURE otherwise
     */
    class IsBarrelMoveFinished : public ConditionNode {
    public:
        IsBarrelMoveFinished(const std::string &name, const NodeConfiguration &config) : ConditionNode(name, config) {}

        NodeStatus tick() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {
                    InputPort<int>("goalPosition"),
            };
        }
    };

    /**
     * Wait for a certain `delay`
     */
    class Wait : public CoroActionNode {
    public:
        Wait(const std::string &name, const NodeConfiguration &config) :
                CoroActionNode(name, config) {}

        NodeStatus tick() override;

        void cleanup(bool halted);

        void halt() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {
                    InputPort<int>("delay"),
            };
        }
    };

}

#endif //MECATRO_P17_NODES_H
