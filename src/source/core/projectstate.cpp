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

#include "../../header/projectstate.h"

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

StockedState* OpenState::set_stocked(){
    return new StockedState();
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

StockedState* LateState::set_stocked(){
    return new StockedState();
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

StockedState* NearlyLateState::set_stocked(){
    return new StockedState();
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
