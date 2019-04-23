//
// Created by juliette on 09/04/19.
//

#include "RobotNodes.h"
#include "RobotNodes.cpp"

std::map<std::string,std::string> positions;

static const char* xml_text = R"(
<root main_tree_to_execute = "MainTree">

	<!--------------------------------------->

    <BehaviorTree ID="CollectPucks">
        <Sequence>
            <Move   pos = positions['P1'] />
            <CollectPuck/>
            <Move   pos = positions['P2'] />
            <CollectPuck/>
            <Move   pos = positions['P3'] />
            <CollectPuck/>
            <Move   pos = positions['P4'] />
            <CollectPuck/>
            <Move   pos = positions['P5'] />
            <CollectPuck/>
            <Move   pos = positions['P6'] />
            <CollectPuck/>
        </Sequence>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="WeightPucks">
        <Repeat nb = "6">
            <Sequence>
                    <Fallback>
                        <Condition ID = "RedPuck"/>
                        <DropPuck/>
                    </Fallback>
                    <TurnCylinder/>
            <Sequence/>
        </Repeat/>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="DropInAccelerator">
        <Repeat nb = "6">
            <Sequence>
                    <Fallback>
                        <Condition ID = "NoPuck"/>
                        <DropPuck/>
                    </Fallback>
                    <TurnCylinder/>
            <Sequence/>
        </Repeat/>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="DropInAccelerator">

    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="MainTree">
        <Sequence>
            <SubTree ID="WeightPucks"/>
            <SubTree ID="CollectPucks"/>
            <SubTree ID="ReachAccelerator"/>
            <SubTree ID="DropInAccelerator"/>
        </Sequence>
    </BehaviorTree>
    <!--------------------------------------->
</root>
 )";

using namespace BT;
using namespace

int main(int argc, char** argv)
{
    BT::BehaviorTreeFactory factory;

    // Important: when the object tree goes out of scope, all the TreeNodes are destroyed
    auto tree = factory.createTreeFromText(xml_text);

    factory.registerSimpleAction("CollectPuck", std::bind(OpenClamp));
    factory.registerSimpleAction("DropPuck", std::bind(DropPuck));
    factory.registerSimpleAction("TurnCylinder", std::bind(TurnCylinder));

    NodeStatus status = NodeStatus::RUNNING;
    // Keep on ticking until you get either a SUCCESS or FAILURE state
    while( status == NodeStatus::RUNNING)
    {
        status = tree.root_node->executeTick();
        SleepMS(1);   // optional sleep to avoid "busy loops"
    }

    return 0;
}