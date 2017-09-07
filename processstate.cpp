#include "processstate.h"

ProcessState::ProcessState()
{

}

_P_TemplateState::_P_TemplateState() : ProcessState()
{

}

ProcessState _P_TemplateState::set_open(){
    return _P_OpenState();
}

ProcessState _P_TemplateState::set_nearly_late(){
    return _P_NearlyLateState();
}

QString _P_TemplateState::to_string(){
    return "TEMPLATE_STATE";
}

_P_OpenState::_P_OpenState() : ProcessState()
{

}

ProcessState _P_OpenState::set_late(){
    return _P_LateState();
}

ProcessState _P_OpenState::set_completed(){
    return _P_CompletedState();
}

ProcessState _P_OpenState::set_nearly_late(){
    return _P_NearlyLateState;
}

QString _P_OpenState::to_string(){
    return "OPEN_STATE";
}

_P_LateState::_P_LateState() : ProcessState()
{

}

ProcessState _P_LateState::set_open(){
    return _P_OpenState();
}

ProcessState _P_LateState::set_completed(){
    return _P_CompletedState();
}

ProcessState _P_LateState::set_nearly_late(){
    return _P_NearlyLateState();
}

QString _P_LateState::to_string(){
    return "LATE_STATE";
}

_P_NearlyLateState::_P_NearlyLateState() : ProcessState()
{

}

ProcessState _P_NearlyLateState::set_open(){
    return _P_OpenState();
}

ProcessState _P_NearlyLateState::set_late(){
    return _P_LateState();
}

ProcessState _P_NearlyLateState::set_completed(){
    return _P_CompletedState();
}

ProcessState _P_NearlyLateState::to_string(){
    return "NEARLY_LATE_STATE";
}

_P_CompletedState::_P_CompletedState() : ProcessState()
{

}

QString _P_CompletedState::to_string(){
    return "COMPLETED_STATE";
}
