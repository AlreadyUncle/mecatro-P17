//
// Created by Alexandre Thomas on 2019-05-03.
//

#include "Nodes.h"

NodeStatus Robot::MoveAhead::tick() {
    // ------------------------
    // Read move instructions from the blackboard
    auto moveForwardInput = getInput<bool>("moveForward");
    auto distanceInput = getInput<int>("distance");
    if (!moveForwardInput) {
        throw BT::RuntimeError("missing required input [moveForward]: ",
                               moveForwardInput.error());
    }
    if (!distanceInput) {
        throw BT::RuntimeError("missing required input [distance]: ",
                               distanceInput.error());
    }
    int distanceToTravelMm = distanceInput.value();
    bool moveForward = moveForwardInput.value();
    if (!moveForward)
        distanceToTravelMm *= -1;

    // Use the appropriate ultrasonic sensor to check for obstacles
    UltrasonicSensor &sensor = moveForward ? frontSensor : backSensor;


    // ------------------------
    // Move or wait logic
    bool isMoveCompleted = false;
    int distanceToTravelUnits = (int) (distanceToTravelMm * UNITS_PER_MM);
    int distanceTraveledUnits = 0;

    while (!isMoveCompleted) {
        // Check for any obstacles ahead
        int distanceToObstacle = sensor.getDistance();
        // if we have an error code (distance < 0), we consider there is no obstacle
        // (note that ahead can mean front or back, depending on the current move direction)
        bool obstacleAhead = (distanceToObstacle > 0 and distanceToObstacle < SENSOR_OBSTACLE_THRESHOLD);

        if (isMoving and !obstacleAhead) {
            if (kangaroo.isMoveCompleted()) {
                isMoveCompleted = true;
                LOG_F(INFO, "straight move completed (total distance : %dmm, %d units)", distanceToTravelMm,
                      distanceToTravelUnits);
            } else {
                LOG_F(1, "straight move going on, no obstacle");
                setStatusRunningAndYield();
            }
        } else {
            if (isMoving) {
                // Moving with obstacle ahead : stop movement and keep in memory current position
                distanceTraveledUnits = kangaroo.getPosition();
                kangaroo.startStraightMove(0, 0); //todo: check if command powerdown is more appropriate
                isMoving = false;
                LOG_F(INFO, "obstacle ahead, stopped movement at distance %d", distanceTraveledUnits);
            } else if (!obstacleAhead) {
                // Idle with no obstacle ahead : start/resume movement
                kangaroo.startStraightMove(distanceToTravelUnits - distanceTraveledUnits, DEFAULT_KANGAROO_SPEED);
                isMoving = true;
            }
            setStatusRunningAndYield();
        }
    }

    cleanup(false);
    return NodeStatus::SUCCESS;
}

void Robot::MoveAhead::cleanup(bool halted) {

}

void Robot::MoveAhead::halt() {
    //todo: stop movement ?
    cleanup(true);
    // Do not forget to call this at the end.
    CoroActionNode::halt();
}





NodeStatus Robot::Turn::tick() {
    // ------------------------
    // Read move instructions from the blackboard
    auto angleInput = getInput<bool>("angle");
    if (!angleInput) {
        throw BT::RuntimeError("missing required input [angle]: ",
                               angleInput.error());
    }
    int angle = angleInput.value();
    // faire la conversion
    int angleUnits = angle

    // ------------------------
    // Move or wait logic
    bool isTurnCompleted = false;

    while (!kangarou.isMoveCompleted()) {
            LOG_F(1, "turning... ");
            setStatusRunningAndYield();
            kangarou.startTurnMove(angleUnits,DEFAULT_ROTATION_SPEED);
    }
    LOG_F(INFO, "straight move completed (total distance : %d degrés, %d units)", angle, angleUnits);

    cleanup(false);
    return NodeStatus::SUCCESS;
}

void Robot::MoveAhead::cleanup(bool halted) {

}

void Robot::Turn::halt() {
    //todo: stop movement ?
    cleanup(true);
    // Do not forget to call this at the end.
    CoroActionNode::halt();
}




NodeStatus Robot::UpdateScore::tick() {
    auto bonusInput = getInput<int>("bonus");
    if (!bonus) {
        throw BT::RuntimeError("missing required input [bonus]: ",
                               bonusInput.error());
    }
    int bonus = bonusInput.value();

    auto score = getInput<int>("oldScore");
    if (!score)
    {
        throw BT::RuntimeError("missing required input [score]: ",
                               score.error() );
    }

    newS = score.value()+bonus
    setOutput("newScore", newS);
    LCD.printToScreenCentered(std::to_string(newS));
    LOG_F(INFO, "Added %d to the score. New score :%d", bonus, newS);
    return NodeStatus::SUCCESS;
}