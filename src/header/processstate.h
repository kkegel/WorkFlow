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

#ifndef PROCESSSTATE_H
#define PROCESSSTATE_H

#include <QString>

#include "state.h"

/**
 * @brief The ProcessState class
 *
 * the ProcessState is for managing the state of a process
 * its a child of state - what in particular doesnt matters
 *
 * ProcessState is only implemented by the Process class
 */

class _P_OpenState;
class _P_NearlyLateState;
class _P_LateState;
class _P_CompletedState;

class ProcessState : public State
{
public:

    ProcessState() : State(){}

    virtual _P_OpenState* set_open() = 0;
    virtual _P_NearlyLateState* set_nearly_late() = 0;
    virtual _P_LateState* set_late() = 0;
    virtual _P_CompletedState* set_completed()= 0;

    /**
     * @brief to_string
     * @return
     *
     * the class name as uppercase QString for identifing the state
     * by other classes (file backend, window frontend)
     */

    virtual QString to_string(){return " ";}

};

/**
 * @brief The TemplateState class
 *
 * in the template state, a process is created,
 * but no one opened it yet.
 * if a process is template, it can also switch to late or nearly late automatically.
 */

class _P_TemplateState : public ProcessState
{
public:

    _P_TemplateState();

    _P_OpenState* set_open() override;
    _P_NearlyLateState* set_nearly_late() override;
    _P_LateState* set_late() override {return nullptr;}
    _P_CompletedState* set_completed() override {return nullptr;}

    QString to_string() override;

};

/**
 * @brief The OpenState class
 *
 * the process is in work and the work is in time with 3 days befor deadline
 */

class _P_OpenState : public ProcessState
{
public:

    _P_OpenState();

    _P_OpenState* set_open() override {return nullptr;}
    _P_LateState* set_late() override;
    _P_CompletedState* set_completed() override;
    _P_NearlyLateState* set_nearly_late() override;

    QString to_string() override;

};

/**
 * @brief The LateState class
 *
 * the process is after deadline and not completed (or opened) yet.
 */

class _P_LateState : public ProcessState
{
public:

    _P_LateState();

    _P_OpenState* set_open() override;
    _P_CompletedState* set_completed() override;
    _P_NearlyLateState* set_nearly_late() override;
    _P_LateState* set_late() override {return nullptr;}

    QString to_string();

};

/**
 * @brief The _P_NearlyLateState class
 *
 * the process is 3 days before deadline (weekends are not counted)
 */

class _P_NearlyLateState : public ProcessState
{
public:

    _P_NearlyLateState();

    _P_OpenState* set_open() override;
    _P_CompletedState* set_completed() override;
    _P_NearlyLateState* set_nearly_late() override {return nullptr;}
    _P_LateState* set_late() override;

    QString to_string() override;

};

/**
 * @brief The CompletedState class
 *
 * the process is completed. over and out.
 */

class _P_CompletedState : public ProcessState
{
public:

    _P_CompletedState();

    _P_OpenState* set_open() override {return nullptr;}
    _P_CompletedState* set_completed() override {return nullptr;}
    _P_NearlyLateState* set_nearly_late() override {return nullptr;}
    _P_LateState* set_late() override {return nullptr;}

    QString to_string() override;
};

#endif // PROCESSSTATE_H
