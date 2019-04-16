//
// Created by juliette on 09/04/19.
//

inline void SleepMS(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


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

#endif //TEST_CLION_ROBOTBEHAVIOUR_H
