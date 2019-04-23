//
// Created by Alexandre Thomas on 2019-04-16.
//
#include "behaviortree_cpp/behavior_tree.h"
#include "dummy_nodes.h"

// This function must be implemented in the .cpp file to create
// a plugin that can be loaded at run-time
BT_REGISTER_NODES(factory) {
    DummyNodes::RegisterNodes(factory);
}

namespace DummyNodes {

    void SleepMS(int x) {
        std::this_thread::sleep_for(std::chrono::milliseconds(x));
    }

    BT::NodeStatus CheckBattery() {
        std::cout << "[ Battery: OK ]" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus GripperInterface::open() {
        _opened = true;
        std::cout << "GripperInterface::open" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus GripperInterface::close() {
        std::cout << "GripperInterface::close" << std::endl;
        _opened = false;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus ApproachObject::tick() {
        std::cout << "ApproachObject: " << this->name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus SaySomething::tick() {
        auto msg = getInput<std::string>("message");
        if (!msg) {
            throw BT::RuntimeError("missing required input [message]: ", msg.error());
        }

        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus SaySomethingSimple(BT::TreeNode &self) {
        auto msg = self.getInput<std::string>("message");
        if (!msg) {
            throw BT::RuntimeError("missing required input [message]: ", msg.error());
        }

        std::cout << "Robot says: " << msg.value() << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus MoveBaseAction::tick() {
        Pose2D goal;
        if (!getInput<Pose2D>("goal", goal)) {
            throw BT::RuntimeError("missing required input [goal]");
        }

        printf("[ MoveBase: STARTED ]. goal: x=%.f y=%.1f theta=%.2f\n",
               goal.x, goal.y, goal.theta);

        _halt_requested.store(false);
        int count = 0;

        // Pretend that "computing" takes 250 milliseconds.
        // It is up to you to check periodicall _halt_requested and interrupt
        // this tick() if it is true.
        while (!_halt_requested && count++ < 25) {
            SleepMS(10);
        }

        std::cout << "[ MoveBase: FINISHED ]" << std::endl;
        return _halt_requested ? BT::NodeStatus::FAILURE : BT::NodeStatus::SUCCESS;
    }
}