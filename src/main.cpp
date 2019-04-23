//
// Created by Alexandre Thomas on 2019-04-16.
//

#include "behaviortree_cpp/bt_factory.h"
// file that contains the custom nodes definitions
#include "strategy_test/dummy_nodes.h"

using namespace BT;
// Note: the name used to register should be the same used in the XML.
using namespace DummyNodes;

// Template specialization to converts a string to Position2D.
namespace BT {
    template<>

    inline Pose2D convertFromString(StringView str) {
        // The next line should be removed...
        printf("Converting string: \"%s\"\n", str.data());

        // We expect real numbers separated by semicolons
        Pose2D output;
        output.x = 1;
        output.y = 3;
        return output;
    }
}

static const char *xml_text = R"(
 <root>
     <BehaviorTree>
        <Sequence>
            <BatteryOK/>
            <SaySomething   message="mission started..." />
            <MoveBase       goal="1;2;3"/>
            <SaySomething   message="mission completed!" />
        </Sequence>
     </BehaviorTree>
 </root>
 )";

int main() {
    // We use the BehaviorTreeFactory to register our custom nodes
    BehaviorTreeFactory factory;

    factory.registerSimpleCondition("BatteryOK", std::bind(CheckBattery));
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<MoveBaseAction>("MoveBase");

    // Trees are created at deployment-time (i.e. at run-time, but only
    // once at the beginning).

    // IMPORTANT: when the object "tree" goes out of scope, all the
    // TreeNodes are destroyed
    auto tree = factory.createTreeFromText(xml_text);

    // To "execute" a Tree you need to "tick" it.
    // The tick is propagated to the children based on the logic of the tree.
    // In this case, the entire sequence is executed, because all the children
    // of the Sequence return SUCCESS.
    NodeStatus status;

    std::cout << "\n--- 1st executeTick() ---" << std::endl;
    status = tree.root_node->executeTick();
    std::cout << "status : " << status << std::endl;

    SleepMS(150);
    std::cout << "\n--- 2nd executeTick() ---" << std::endl;
    status = tree.root_node->executeTick();
    std::cout << "status : " << status << std::endl;

    SleepMS(150);
    std::cout << "\n--- 3rd executeTick() ---" << std::endl;
    status = tree.root_node->executeTick();
    std::cout << "status : " << status << std::endl;

    std::cout << std::endl;

    return 0;
}

/* Expected output:
*
       [ Battery: OK ]
       GripperInterface::open
       ApproachObject: approach_object
       GripperInterface::close
*/
