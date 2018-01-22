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

#include "../../header/datelib.h"

QDate first_day_of_kw(int kw, int year){

    QDate date(year,1,1);

    while(date.dayOfWeek() != 1){
        date = date.addDays(1);
    }

    date = date.addDays((kw-1)*7);

    return date;
}

bool is_valid_difference(QDate start, QDate end){
 
    if(start.toJulianDay() < end.toJulianDay()){
        return true;
    }
    return false;
}
