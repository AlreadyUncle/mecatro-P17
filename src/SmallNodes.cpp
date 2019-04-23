//
// Created by juliette on 16/04/19.
//

#include "SmallNodes.h"

#ifndef TEST_CLION_SMALLNODES_H
#define TEST_CLION_SMALLNODES_H


namespace SmallNodes
{
    BT::NodeStatus OpenClamp()
    {
        return BT::NodeStatus::SUCCESS;
    };

    BT::NodeStatus CloseClamp()
    {
        return BT::NodeStatus::SUCCESS;
    };

    BT::NodeStatus Turn90()
    {
        return BT::NodeStatus::SUCCESS;
    };

    BT::NodeStatus ChasseNeige()
    {
        return BT::NodeStatus::SUCCESS;
    };

    BT::NodeStatus Move::tick() override {

        Optional <std::string> goal = getInput<std::string>("pos");
        goal = BT::convertFromString(goal)

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