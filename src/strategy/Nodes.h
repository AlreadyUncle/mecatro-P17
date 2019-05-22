//
// Created by Alexandre Thomas on 2019-05-03.
//

#ifndef MECATRO_P17_NODES_H
#define MECATRO_P17_NODES_H

#include "behaviortree_cpp/behavior_tree.h"
#include "loguru.hpp"
#include "../components/UltrasonicSensor.h"
#include "../components/Kangaroo.h"
#include "../components/AX12.h"
#include "../components/LCD.h"

#define SERIAL_PORT_KANGAROO            "/dev/ttyUSB0"

// Kangaroo
#define UNITS_PER_MM                    5.669
#define UNITS_PER_DEGREE                13.89
#define DEFAULT_KANGAROO_SPEED          500
#define DEFAULT_KANGAROO_ROTATION_SPEED 500

// AX-12
#define DEFAULT_AX12_WHEEL_SPEED        500
#define AX_ID_BR_PUSH_RIGHT_ATOM        6       // BR stands for big robot
#define AX_ID_BR_PUSH_LEFT_ATOM         2
#define AX_ID_BR_MOVE_ARM_SIDE          3
#define AX_ID_BR_MOVE_ARM_FRONT         4
#define AX_ID_BR_TURN_ARM               5

// Other Pins definition
#define SENSOR_OBSTACLE_THRESHOLD       100     // distance (in mm) under which obstacles are considered
#define SENSOR_TRIGGER_PIN              23
#define SENSOR_ECHO_PIN_FRONT           24
#define SENSOR_ECHO_PIN_BACK            25

using namespace BT;

namespace Robot {

    /**
     * Move (forward or backward, depending on the signe of `distance`) a certain distance, while checking the obstacles.
     * If there are any obstacles, stop and wait.
     * Return RUNNING until the movement is completed, then return SUCCESS.
     */
    class MoveAhead : public CoroActionNode {
    public:
        MoveAhead(const std::string &name, const NodeConfiguration &config, UltrasonicSensor &frontSensor,
                  UltrasonicSensor &backSensor, Kangaroo &kangaroo) :
                CoroActionNode(name, config),
                frontSensor(frontSensor),
                backSensor(backSensor),
                kangaroo(kangaroo) {}

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
        bool isMoving = false;
        UltrasonicSensor &frontSensor;
        UltrasonicSensor &backSensor;
        Kangaroo &kangaroo;
    };

    /**
     * Turn a certain angle
     */
    class Turn : public CoroActionNode {
    public:
        Turn(const std::string &name, const NodeConfiguration &config,
             Kangaroo &kangaroo) :
                CoroActionNode(name, config),
                kangaroo(kangaroo) {}

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
        Kangaroo &kangaroo;
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

    class ActivatePump : public CoroActionNode {

    };

    /**
     * Update the internal score estimation, and print it to the LCD screen.
     */
    class UpdateScore : public SyncActionNode {
    public:
        UpdateScore(const std::string &name, const NodeConfiguration &config, LCD &lcd) :
                SyncActionNode(name, config),
                lcd(lcd) {}

        NodeStatus tick() override;

        static PortsList providedPorts() {
            InputPort<int>("pointsEarned");
        }

    private:
        int currentScore = 0;
        LCD &lcd;
    };

    class JackUnplugged : public ConditionNode {

    };
}

#endif //MECATRO_P17_NODES_H
