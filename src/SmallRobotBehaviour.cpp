//
// Created by juliette on 05/03/19.
//

#include "SmallRobotBehaviour.h"

std::map<std::string,std::string> positions;

static const char* xml_text = R"(
<root main_tree_to_execute = "MainTree">

	<!--------------------------------------->

    <BehaviorTree ID="PushPuck">
        <Sequence>
            <Move   pos = positions['M'] />
            <Turn90/>
            <Move   pos = positions['P1'] />
            <OpenClamp/>

            <ReactiveSequence>
                <Fallback>
                    <Condition ID = "NoObstacle"/>
                    <Avoid/>
                </Fallback>
                <Move   pos = positions['P2'] />
            </ReactiveSequence>
            <CloseClamp/>
        </Sequence>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="GetG">
        <Sequence>
            <Move   pos = positions['G']>
            <OpenClamp/>
            <Grab_G>
            <CloseClamp/>
        <Sequence/>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="WeightG">
        <ReactiveSequence>
            <Fallback>
                <Condition ID = "NoObstacle"/>
                <Avoid/>
            </Fallback>
            <Sequence>
                <Move   pos = {B} />
                <Move   pos = {J} />
                <CheckRobot/>
                <Move   pos = positions['scale'] />
                <OpenClamp/>
            </Sequence>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="ChasseNeige">
        <ChasseNeige/>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="MainTree">
        <Sequence>
            <SubTree ID="PushPuck"/>
            <SubTree ID="GetG"/>
            <SubTree ID="WeightG"/>
            <SubTree ID="ChasseNeige"/>
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

    factory.registerSimpleAction("OpenClamp", std::bind(OpenClamp));
    factory.registerSimpleAction("CloseClamp", std::bind(CloseCLamp));
    factory.registerSimpleAction("Turn90", std::bind(Turn90));
    factory.registerSimpleAction("Grab_G", std::bind(Grab_G));
    factory.registerSimpleAction("ChasseNeige", std::bind(ChasseNeige));

    NodeStatus status = NodeStatus::RUNNING;
    // Keep on ticking until you get either a SUCCESS or FAILURE state
    while( status == NodeStatus::RUNNING)
    {
        status = tree.root_node->executeTick();
        SleepMS(1);   // optional sleep to avoid "busy loops"
    }

    return 0;
}