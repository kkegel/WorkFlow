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

#include "../../header/projectitem.h"

ProjectItem::ProjectItem(QDate start_time, QDate end_time)
{
    this->START_TIME = start_time;
    this->END_TIME = end_time;
}

QDate ProjectItem::get_start_time(){

    return START_TIME;
}

QDate ProjectItem::get_end_time(){

    return END_TIME;
}

