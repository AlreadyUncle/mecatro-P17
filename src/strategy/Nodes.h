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

#define SERIAL_PORT_KANGAROO            "/dev/serial0"

#define SENSOR_OBSTACLE_THRESHOLD       100     // distance (in mm) under which obstacles are considered
#define UNITS_PER_MM                    5.6666  // Kangaroo parameters
#define UNITS_PER_DEGREE                13.89
#define DEFAULT_KANGAROO_SPEED          10
#define DEFAULT_ROTATION_SPEED          10

using namespace BT;

namespace Robot {

    /**
     * Move (forward or backward) a certain distance, while checking the obstacles.
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
                    InputPort<bool>("moveForward"),
                    InputPort<int>("distance")
            };
        }

    private:
        bool isMoving = false;
        UltrasonicSensor &frontSensor;
        UltrasonicSensor &backSensor;
        Kangaroo &kangaroo;
    };

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
     * Activate an AX12 (in mode joint or wheel) to make it move to position `pos`.
     * Return RUNNING until the movement is completed, then return SUCCESS.
     */
    class MoveAX12 : public CoroActionNode {
    public:
        MoveAX12(const std::string &name, const NodeConfiguration &config, AX12 &ax) :
                CoroActionNode(name, config),
                _ax(ax) {}

        NodeStatus tick() override;

        void cleanup(bool halted);

        void halt() override;

        // It is mandatory to define this static method.
        static PortsList providedPorts() {
            return {InputPort<int>("pos"),
                    InputPort<std::string>("mode")};
        }

    private:
        AX12 _ax;
    };

    class ActivatePump : public CoroActionNode {

    };

    class UpdateScore : public SyncActionNode {
    public:
        Turn(const std::string &name, const NodeConfiguration &config, LCD &lcd) :
                CoroActionNode(name, config),
                LCD(lcd) {}

        NodeStatus tick() override;

        static PortsList providedPorts() {
            InputPort<int>("bonus"),
            InputPort<int>("oldScore")
            OutputPort<int>("newScore");
        }
    };

    class JackUnplugged : public ConditionNode {

    };
}

#endif //MECATRO_P17_NODES_H
