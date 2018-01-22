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

#include "../../header/datecontainer.h"

DateContainer::DateContainer(QDate front, QDate back, int width)
{
    this->front_date = front;
    this->back_date = back;
    this->width_pixel = width;
}

QDate DateContainer::get_front_date(){

    return front_date;
}

QDate DateContainer::get_back_date(){

    return back_date;
}

void DateContainer::set_front_date(QDate front){

    this->front_date = front;
}

void DateContainer::set_back_date(QDate back){

    this->back_date = back;
}

int DateContainer::get_width_pixel(){

    return width_pixel;
}

void DateContainer::set_width_pixel(int width){

    this->width_pixel = width;
}
