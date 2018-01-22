/**
  This file is part of WorkFlow.

  WorkFlow is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  WorkFlow is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

  Copyright (C) Karl Kegel (github: kkegel) 2018
*/

#include "../../header/processstate.h"

_P_TemplateState::_P_TemplateState() : ProcessState()
{

}

_P_OpenState* _P_TemplateState::set_open(){
    return new _P_OpenState();
}

_P_NearlyLateState* _P_TemplateState::set_nearly_late(){
    return new _P_NearlyLateState();
}

QString _P_TemplateState::to_string(){
    return "TEMPLATE_STATE";
}

_P_OpenState::_P_OpenState() : ProcessState()
{

}

_P_LateState* _P_OpenState::set_late(){
    return new _P_LateState();
}

_P_CompletedState* _P_OpenState::set_completed(){
    return new _P_CompletedState();
}

_P_NearlyLateState* _P_OpenState::set_nearly_late(){
    return new _P_NearlyLateState();
}

QString _P_OpenState::to_string(){
    return "OPEN_STATE";
}

_P_LateState::_P_LateState() : ProcessState()
{

}

_P_OpenState* _P_LateState::set_open(){
    return new _P_OpenState();
}

_P_CompletedState* _P_LateState::set_completed(){
    return new _P_CompletedState();
}

_P_NearlyLateState* _P_LateState::set_nearly_late(){
    return new _P_NearlyLateState();
}

QString _P_LateState::to_string(){
    return "LATE_STATE";
}

_P_NearlyLateState::_P_NearlyLateState() : ProcessState()
{

}

_P_OpenState* _P_NearlyLateState::set_open(){
    return new _P_OpenState();
}

_P_LateState* _P_NearlyLateState::set_late(){
    return new _P_LateState();
}

_P_CompletedState* _P_NearlyLateState::set_completed(){
    return new _P_CompletedState();
}

QString _P_NearlyLateState::to_string(){
    return "NEARLY_LATE_STATE";
}

_P_CompletedState::_P_CompletedState() : ProcessState()
{

}

QString _P_CompletedState::to_string(){
    return "COMPLETED_STATE";
}
