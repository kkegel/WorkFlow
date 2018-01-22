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

#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QDate>
#include <QString>
#include "state.h"

/**
 * @brief The ProjectItem class
 *
 * a project item is either a Project or a Process
 * this generalization is importent for layout handling at
 * the front end.
 */

class ProjectItem
{
public:

    ProjectItem(QDate start_time, QDate end_time);
    ProjectItem(){}

    QDate get_start_time();

    QDate get_end_time();

    virtual QString get_state() = 0;
    virtual QString get_title() = 0;

    QDate START_TIME;
    QDate END_TIME;

private:


};

#endif // PROJECTITEM_H
