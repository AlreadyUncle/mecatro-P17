//
// Created by juliette on 16/04/19.
//

#include "RobotNodes.h"

namespace RobotNodes
{
    BT::NodeStatus CollectPuck()
    {
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus DropPuck()
    {
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus TurnCylinder()
    {
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus Move::tick() override {

        Optional <std::string> goal = getInput<std::string>("pos");
        goal = BT::convertFromString(goal);

        if (not isMoving) {
            // lancer le mouvement
            isMoving = true
            return NodeStatus::RUNNING
        }
        if (posReached) {
            isMoving = false
            // mettre à jour la position du robot
            return NodeStatus::SUCCESS
        }
        return NodeStatus::RUNNING;
    }
};