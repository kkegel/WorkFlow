#include "datelib.h"

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
