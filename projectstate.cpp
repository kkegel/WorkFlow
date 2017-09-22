#include "projectstate.h"

OpenState::OpenState() : ProjectState()
{

}

NearlyLateState* OpenState::set_nearly_late(){
    return new NearlyLateState();
}

LateState* OpenState::set_late(){
    return new LateState();
}

FinishedState* OpenState::set_finished(){
    return new FinishedState();
}

QString OpenState::to_string(){
    return "OPEN_STATE";
}

LateState::LateState() : ProjectState()
{

}

OpenState* LateState::set_open(){
    return new OpenState();
}

NearlyLateState* LateState::set_nearly_late(){
    return new NearlyLateState();
}

FinishedState* LateState::set_finished(){
    return new FinishedState();
}

QString LateState::to_string(){
    return "LATE_STATE";
}

NearlyLateState::NearlyLateState() : ProjectState()
{

}

OpenState* NearlyLateState::set_open(){
    return new OpenState();
}

LateState* NearlyLateState::set_late(){
    return new LateState();
}

FinishedState* NearlyLateState::set_finished(){
    return new FinishedState();
}

QString NearlyLateState::to_string(){
    return "NEARLY_LATE_STATE";
}

FinishedState::FinishedState() : ProjectState(){

}

OpenState* FinishedState::set_open(){
    return new OpenState();
}

StockedState* FinishedState::set_stocked(){
    return new StockedState();
}

QString FinishedState::to_string(){
    return "FINISHED_STATE";
}

StockedState::StockedState() : ProjectState()
{

}

OpenState* StockedState::set_open(){
    return new OpenState();
}

QString StockedState::to_string(){
    return "STOCKED_STATE";
}
