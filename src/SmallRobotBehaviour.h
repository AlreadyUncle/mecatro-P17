//
// Created by juliette on 05/03/19.
//
namespace behaviourtree
{
    inline void SleepMS(int ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    BT::NodeStatus PushPuck();

    BT::NodeStatus GetG();

    BT::NodeStatus WeightG();

    BT::NodeStatus ChasseNeige();


    BT::NodeStatus MoveTo_M();

    BT::NodeStatus MoveTo_P1();

    BT::NodeStatus MoveTo_P2();

    BT::NodeStatus OpenPlier();

    BT::NodeStatus CloseClamp();

    void RegisterNodes(BT::BehaviorTreeFactory& factory);
}