//
// Created by juliette on 05/03/19.
//
inline void SleepMS(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


BT::NodeStatus OpenClamp()
{
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus CloseClamp()
{
    return BT::NodeStatus::SUCCESS;
}

BT::NodeStatus Turn90()
{
    return BT::NodeStatus::SUCCESS;
}


struct Position2D
{
    double x;
    double y;
};

class Move: public SyncActionNode
{
    public:
    Move(const std::string& name, const NodeConfiguration& config):
            SyncActionNode(name,config)
    {}

    static PortsList providedPorts()
    {
        return { OutputPort<Point>("pos") };
    }

    NodeStatus tick() override {
        {
            Optional <std::string> goal = getInput<std::string>("pos");
            goal = BT::convertFromString(goal)

            // Si mouvement non en cours -> lancer le mouvement
            // Sinon, si position atteinte -> Renvoyer SUCCESS et mettre à jour
            //  la position du robot et spécifier que le mouvement est terminé
            // Sinon, renvoyer RUNNING

            return NodeStatus::SUCCESS;
        }
    }
}

template <> inline Position2D convertFromString(StringView str)
{
    auto parts = splitString(str, ';');
    if (parts.size() != 2)
    {
        throw RuntimeError("invalid input)");
    }
    else{
        Point output;
        output.x     = convertFromString<double>(parts[0]);
        output.y     = convertFromString<double>(parts[1]);
        return output;
    }
}

void RegisterNodes(BT::BehaviorTreeFactory& factory);
{
}