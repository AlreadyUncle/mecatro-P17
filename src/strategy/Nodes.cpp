//
// Created by Alexandre Thomas on 2019-05-03.
//

#include "Nodes.h"

// ------ Kangaroo -------
NodeStatus Robot::MoveAhead::tick() {
    int speed = _bigRobot ? KANGAROO_SPEED_BR : KANGAROO_SPEED_SR;
    int threshold = _bigRobot ? SENSOR_OBSTACLE_THRESHOLD_BR : SENSOR_OBSTACLE_THRESHOLD_SR;
    float unitsPerMm = _bigRobot ? UNITS_PER_MM_BR : UNITS_PER_MM_SR;

    // ------------------------
    // Read move instructions from the blackboard
    auto distanceInput = getInput<int>("distance");
    if (!distanceInput) {
        throw BT::RuntimeError("missing required input [distance]: ",
                               distanceInput.error());
    }
    int distanceToTravelMm = distanceInput.value();

    // Use the appropriate ultrasonic sensor to check for obstacles
    UltrasonicSensor &sensorLeft = distanceToTravelMm >= 0 ? _frontSensorLeft : _backSensorLeft;
    UltrasonicSensor &sensorRight = distanceToTravelMm >= 0 ? _frontSensorRight : _backSensorRight;

    // ------------------------
    // Move or wait logic
    bool isMoveCompleted = false;
    int distanceToTravelUnits = (int) (distanceToTravelMm * unitsPerMm);
    int distanceTraveledUnits = 0;

    while (!isMoveCompleted) {
        // Check for any obstacles ahead
        int distanceToObstacleLeft = sensorLeft.getDistance();
        int distanceToObstacleRight;
        if (_bigRobot) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            distanceToObstacleRight = sensorRight.getDistance();
        } else
            distanceToObstacleRight = distanceToObstacleLeft;
        // if we have an error code (distance < 0), we consider there is no obstacle
        // (note that ahead can mean front or back, depending on the current move direction)
        bool obstacleAhead = ((distanceToObstacleLeft > 0 and distanceToObstacleLeft < threshold) or
                              (distanceToObstacleRight > 0 and distanceToObstacleRight < threshold));

//todo: update distance traveled at each step with getp ?

        if (!isMoving and !obstacleAhead) {
            // Idle with no obstacle ahead : start/resume movement
            LOG_F(INFO, "no obstacle ahead, starting or resuming movement with %d units left to do",
                  distanceToTravelUnits - distanceTraveledUnits);

            // Our small robot moves straight when it's told to turn, and vice versa
            if (_bigRobot)
                _kangaroo.startStraightMove(distanceToTravelUnits - distanceTraveledUnits, speed);
            else
                _kangaroo.startTurnMove(distanceToTravelUnits - distanceTraveledUnits, speed);

            isMoving = true;
            setStatusRunningAndYield();
        } else if (isMoving and !obstacleAhead) {
            if (_kangaroo.isMoveCompleted()) {
                isMoveCompleted = true;
                LOG_F(INFO, "straight move completed (total distance : %dmm, %d units)", distanceToTravelMm,
                      distanceToTravelUnits);
            } else {
                LOG_F(1, "straight move going on, no obstacle");
                setStatusRunningAndYield();
            }
        } else if (isMoving and obstacleAhead) {
            // Moving with obstacle ahead : stop movement and keep in memory current position
            distanceTraveledUnits += _kangaroo.getPosition();
            if (_bigRobot)
                _kangaroo.startStraightMove(0, 0);
            else
                _kangaroo.startTurnMove(0, 0);

            isMoving = false;
            LOG_F(INFO, "obstacle ahead, stopped movement at distance %d", distanceTraveledUnits);
            setStatusRunningAndYield();

        } else {
            LOG_F(INFO, "obstacle ahead, movement already stopped, waiting...");
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
    int speed = _bigRobot ? KANGAROO_ROTATION_SPEED_BR : KANGAROO_ROTATION_SPEED_SR;
    float unitsPerDegree = _bigRobot ? UNITS_PER_DEGREE_BR : UNITS_PER_DEGREE_SR;

    // ------------------------
    // Read move instructions from the blackboard
    auto angleInput = getInput<int>("angle");
    if (!angleInput) {
        throw BT::RuntimeError("missing required input [angle]: ",
                               angleInput.error());
    }
    int angleDegrees = angleInput.value();
    int angleUnits = (int) (angleDegrees * unitsPerDegree);

    // ------------------------
    // Move or wait logic
    if (_bigRobot)
        _kangaroo.startTurnMove(angleUnits, speed);
    else
        _kangaroo.startStraightMove(angleUnits, speed);

    bool isTurnCompleted = false;
    while (!isTurnCompleted) {
        LOG_F(1, "turning... ");
        isTurnCompleted = _kangaroo.isMoveCompleted();
        setStatusRunningAndYield();
    }
    LOG_F(INFO, "turn move completed (total distance : %d degrees, %d units)", angleDegrees, angleUnits);

    cleanup(false);
    return NodeStatus::SUCCESS;
}

void Robot::Turn::cleanup(bool halted) {

}

void Robot::Turn::halt() {
    //todo: stop movement ?
    cleanup(true);
    // Do not forget to call this at the end.
    CoroActionNode::halt();
}

// ------ AX12 -------
NodeStatus Robot::MoveAX12Joint::tick() {
    // ------------------------
    // Read move instructions from the blackboard
    auto positionInput = getInput<int>("pos");
    if (!positionInput) {
        throw BT::RuntimeError("missing required input [pos]: ",
                               positionInput.error());
    }
    auto goalPosition = positionInput.value();

    // ------------------------
    // Move logic
    _ax.setMode(joint);
    _ax.setSpeed(DXL_JOINT_SPEED); // 0 : maximum speed (same as 1023)
    _ax.goToPositionJointMode(goalPosition);

    auto currentPosition = _ax.getPosition();
    while (std::abs(goalPosition - currentPosition) > DXL_MOVING_STATUS_THRESHOLD) {
        currentPosition = _ax.getPosition();
        LOG_F(INFO, "[id %d] moving ; GoalPos:%03d CurrentPos:%03d", _ax.ID, goalPosition, currentPosition);
        setStatusRunningAndYield();
    }

    cleanup(false);
    return NodeStatus::SUCCESS;
}

void Robot::MoveAX12Joint::cleanup(bool halted) {
}

void Robot::MoveAX12Joint::halt() {
    CoroActionNode::halt();
}

NodeStatus Robot::MoveAX12Wheel::tick() {
    // Get inputs from the blackboard
    auto distanceInput = getInput<int>("distance");
    if (!distanceInput) {
        throw BT::RuntimeError("missing required input [distance]: ",
                               distanceInput.error());
    }
    auto distance = distanceInput.value();

    // Rotation direction (CW or CCW) is controlled by the 10th bit
    bool isCW = distance >= 0;
    int speed = isCW ? DXL_WHEEL_SPEED + 1024 : DXL_WHEEL_SPEED;
    int zero = isCW ? 1024 : 0;
    auto duration = std::chrono::milliseconds((int) (1000 * abs(distance) / DXL_WHEEL_SPEED));

    LOG_F(INFO, "goal duration (ms) : %d", (int) (1000 * abs(distance) / DXL_WHEEL_SPEED));
    LOG_F(INFO, "speed : %d", speed);
    LOG_F(INFO, "zero : %d", zero);

    // Start the movement
    _ax.setMode(wheel);
    auto initialTime = std::chrono::system_clock::now();
    _ax.setSpeed(speed);

    auto currentPosition = _ax.getPosition();
    auto currentTime = std::chrono::system_clock::now();
    while (currentTime < initialTime + duration) {
        currentPosition = _ax.getPosition();
        currentTime = std::chrono::system_clock::now();
        LOG_F(INFO, "[id %d] moving ; GoalDuration:%03d CurrentDuration:%03d CurrentPos:%03d", _ax.ID,
              duration.count(), (currentTime - initialTime).count(), currentPosition);
        setStatusRunningAndYield();
    }

    // Stop the movement
    _ax.setSpeed(zero);


    cleanup(false);
    return NodeStatus::SUCCESS;
}

void Robot::MoveAX12Wheel::cleanup(bool halted) {

}

void Robot::MoveAX12Wheel::halt() {
    CoroActionNode::halt();
}

// ------ Other -------
NodeStatus Robot::UpdateScore::tick() {
    auto pointsEarnedInput = getInput<int>("pointsEarned");
    if (!pointsEarnedInput) {
        throw BT::RuntimeError("missing required input [pointsEarned]: ",
                               pointsEarnedInput.error());
    }
    int pointsEarned = pointsEarnedInput.value();
    currentScore += pointsEarned;

    _lcd.printToScreenCentered("Score : " + std::to_string(currentScore));
    LOG_F(INFO, "Added %d to the score. New current score :%d", pointsEarned, currentScore);

    return NodeStatus::SUCCESS;
}

NodeStatus Robot::ActivateRelayModule::tick() {
    _relayModule.turnOn();
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::DeactivateRelayModule::tick() {
    _relayModule.turnOff();
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::IsBarrelMoveFinished::tick() {
    // Get inputs from the blackboard
    auto goalPositionInput = getInput<int>("goalPosition");
    if (!goalPositionInput) {
        throw BT::RuntimeError("missing required input [goalPosition]: ",
                               goalPositionInput.error());
    }

    auto goalPosition = goalPositionInput.value();

    if (Encoder::globalBarrelCounter >= goalPosition) {
        LOG_F(INFO, "Barrel Move finished (goalPosition %d, currentPosition %d)", goalPosition,
              Encoder::globalBarrelCounter);
        return NodeStatus::SUCCESS;
    } else
        return NodeStatus::FAILURE;
}

NodeStatus Robot::Wait::tick() {
    // Get inputs from the blackboard
    auto delayInput = getInput<int>("delay");
    if (!delayInput) {
        throw BT::RuntimeError("missing required input [delay]: ",
                               delayInput.error());
    }
    auto delayMs = delayInput.value();
    LOG_F(INFO, "Waiting for duration %dms", delayMs);

    auto delayDuration = std::chrono::milliseconds(delayMs);
    auto initialTime = std::chrono::system_clock::now();
    auto currentTime = std::chrono::system_clock::now();

    while (currentTime < initialTime + delayDuration) {
        currentTime = std::chrono::system_clock::now();
        setStatusRunningAndYield();
    }

    LOG_F(INFO, "Finished waiting");

    cleanup(false);
    return NodeStatus::SUCCESS;
}

void Robot::Wait::cleanup(bool halted) {

}

void Robot::Wait::halt() {
    CoroActionNode::halt();
}
