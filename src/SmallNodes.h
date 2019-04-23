//
// Created by juliette on 05/03/19.
//

namespace SmallNodes
{
    struct Position2D {
        double x;
        double y;
    };

    inline void SleepMS(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }


    BT::NodeStatus OpenClamp();

    BT::NodeStatus CloseClamp();

    BT::NodeStatus Turn90();

    BT::NodeStatus ChasseNeige();

    class Move : public SyncActionNode {
    public:
        Move(const std::string &name, const NodeConfiguration &config) :
                SyncActionNode(name, config) {}

        static PortsList providedPorts() {
            return {OutputPort<Point>("pos")};
        };

        NodeStatus tick() override;
    };

    template<>
    inline Position2D convertFromString(StringView str) {
        auto parts = splitString(str, ';');
        if (parts.size() != 2) {
            throw RuntimeError("invalid input)");
        } else {
            Point output;
            output.x = convertFromString<double>(parts[0]);
            output.y = convertFromString<double>(parts[1]);
            return output;
        }
    };

    void RegisterNodes(BT::BehaviorTreeFactory &factory);
}