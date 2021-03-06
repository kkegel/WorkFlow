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

#ifndef PROCESS_H
#define PROCESS_H

#include <QString>
#include <QDate>
#include <QDateTime>

#include "projectitem.h"
#include "processstate.h"

/**
 * @brief The Process class
 *
 * a process is a part of an project and a project can have lots of processes.
 * it is thought as a sub-action of a project, which is defined by start and end date,
 * a unic name, a responsible and a state.
 *
 * the state of a process has effects to the state of the owning project.
 */

class Process : public ProjectItem
{
public:

    Process(QDate start_date, QDate end_date, QString name,
            QString responsible, QString state_hint, QString annotation);
    Process(){}

    QString get_name();   
    QString get_responsible();
    QString get_annotation();
    void set_annotation(QString an);

    /*
     * state actions
     * show in processstate.h for more information
     */

    bool set_open();
    bool set_late();
    bool set_completed();
    bool set_nearly_late();

    QString get_state() override;

    QString get_title() override;

    bool STARTED = false;

private:

    /**
     * @brief NAME
     *
     * the unic name of the process
     */

    QString NAME = "";

    QString annotation = "";

    /**
     * @brief responsible
     * the person/team... who is responsible for the process
     * NOT the creator by default!
     */

    QString responsible = "";

    /**
     * @brief state
     *
     * the current state of the process.
     * more in processstate.xml
     */

    ProcessState* state = new _P_TemplateState;

    /**
     * @brief determine_state
     * @param state_hint
     *
     * changes the state to what is recommended with given
     * information like timing and the state_hint
     *
     * look in the implementation for more information about the hint.
     */

    void determine_state(QString state_hint);

};

#endif // PROCESS_H
