#include "projectstate.h"

ProjectState::ProjectState() : State()
{

}

OpenState::OpenState() : ProjectState()
{

}

ProjectState OpenState::set_nearly_late(){
    return NearlyLateState();
}

ProjectState OpenState::set_late(){
    return LateState();
}

ProjectState OpenState::set_finished(){
    return FinishedState();
}

QString OpenState::to_string(){
    return "OPEN_STATE";
}

LateState::LateState() : ProjectState()
{

}

ProjectState LateState::set_open(){
    return OpenState();
}

ProjectState LateState::set_nearly_late(){
    return NearlyLateState();
}

ProjectState LateState::set_finished(){
    return FinishedState();
}

QString LateState::to_string(){
    return "LATE_STATE";
}

NearlyLateState::NearlyLateState() : ProjectState()
{

}

ProjectState NearlyLateState::set_open(){
    return OpenState();
}

ProjectState NearlyLateState::set_late(){
    return LateState();
}

ProjectState NearlyLateState::set_finished(){
    return FinishedState();
}

QString NearlyLateState::to_string(){
    return "NEARLYLATE_STATE";
}

FinishedState::FinishedState() : ProjectState(){

}

ProjectState FinishedState::set_open(){
    return OpenState();
}

ProjectState FinishedState::set_stocked(){
    return StockedState();
}

QString FinishedState::to_string(){
    return "FINISHED_STATE";
}

StockedState::StockedState() : ProjectState()
{

}

ProjectState StockedState::set_open(){
    return OpenState();
}

QString StockedState::to_string(){
    return "STOCKED_STATE";
}
