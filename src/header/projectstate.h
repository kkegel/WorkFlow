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

#ifndef PROJECTSTATE_H
#define PROJECTSTATE_H

#include <QString>

#include "state.h"

class OpenState;
class NearlyLateState;
class LateState;
class FinishedState;
class StockedState;

class ProjectState : public State
{
public:

    ProjectState() : State(){}

    virtual OpenState* set_open() = 0;
    virtual NearlyLateState* set_nearly_late() = 0;
    virtual LateState* set_late() = 0;
    virtual FinishedState* set_finished() = 0;
    virtual StockedState* set_stocked() = 0;

    virtual QString to_string() = 0;
};

class OpenState : public ProjectState
{
public:

    OpenState();

    OpenState* set_open() override {return nullptr;}
    NearlyLateState* set_nearly_late() override;
    LateState* set_late() override;
    FinishedState* set_finished() override;
    StockedState* set_stocked() override;

    QString to_string() override;
};

class LateState : public ProjectState
{
public:

    LateState();

    OpenState* set_open() override;
    NearlyLateState* set_nearly_late() override;
    LateState* set_late() override {return nullptr;}
    FinishedState* set_finished() override;
    StockedState* set_stocked() override;

    QString to_string() override;
};

class NearlyLateState : public ProjectState
{
public:

    NearlyLateState();

    OpenState* set_open() override;
    NearlyLateState* set_nearly_late() override {return nullptr;}
    LateState* set_late() override;
    FinishedState* set_finished() override;
    StockedState* set_stocked() override;

    QString to_string() override;
};

class FinishedState : public ProjectState
{
public:

    FinishedState();

    OpenState* set_open() override;
    NearlyLateState* set_nearly_late() override {return nullptr;}
    LateState* set_late() override {return nullptr;}
    FinishedState* set_finished() override {return nullptr;}
    StockedState* set_stocked() override;

    QString to_string() override;
};

class StockedState : public ProjectState
{
public:

    StockedState();

    OpenState* set_open() override;
    NearlyLateState* set_nearly_late() override {return nullptr;}
    LateState* set_late() override {return nullptr;}
    FinishedState* set_finished() override {return nullptr;}
    StockedState* set_stocked() override {return nullptr;}


    QString to_string() override;
};

#endif // PROJECTSTATE_H
