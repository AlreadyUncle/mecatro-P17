//
// Created by juliette on 05/03/19.
//

#include "behaviortree.h"

static const char* xml_text = R"(
<root main_tree_to_execute = "MainTree">

	<!--------------------------------------->

    <BehaviorTree ID="PushPuck">
        <Sequence>
            <MoveTo_M/>
            <Turn_90/>
            <MoveTo_P1/>
            <OpenClamp/>
            <ReactiveSequence>
                <Fallback>
                    <Condition ID = "NoObstacle"/>
                    <Avoid/>
                </Fallback>
                <MoveTo_P2/>
            </ReactiveSequence>
            <CloseClamp/>
        </Sequence>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="GetG">
        <Sequence>
            <MoveTo_G/>
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
                <MoveTo_B/>
                <MoveTo_J/>
                <CheckRobot/>
                <MoveTo_Scale/>
                <OpenClamp/>
            </Sequence>
    </BehaviorTree>

    <!--------------------------------------->

    <BehaviorTree ID="ChasseNeige">

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

int main(int argc, char** argv)
{
    BT::BehaviorTreeFactory factory;
    SmallRobot::RegisterNodes(factory);

    // Important: when the object tree goes out of scope, all the TreeNodes are destroyed
    auto tree = factory.createTreeFromText(xml_text);

    factory.registerNodeType<PushPuck>("PushPuck");

    tree.root_node->executeTick();

    return 0;

}


BT::NodeStatus PushPuck()
{
    return BT::NodeStatus::SUCCESS;
}
