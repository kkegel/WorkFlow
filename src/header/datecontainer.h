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

#ifndef DATECONTAINER_H
#define DATECONTAINER_H

#include <QString>
#include <QDate>
#include <QDateTime>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <vector>

#include "project.h"
#include "process_.h"
#include "projectitem.h"
#include "projectmanager.h"

class DateContainer
{
public:

    DateContainer(QDate front, QDate back, int width);
    DateContainer(){}

    QDate get_front_date();
    QDate get_back_date();
    void set_front_date(QDate front);
    void set_back_date(QDate back);
    int get_width_pixel();
    void set_width_pixel(int width);

    QDate front_date;
    QDate back_date;

    int width_pixel;

};

#endif // DATECONTAINER_H
