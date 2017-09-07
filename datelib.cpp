#include "datelib.h"

QDate first_day_of_kw(int kw, int year){

    QDate date(year,1,1);

    while(date.dayOfWeek() != 1){
        date.addDays(1);
    }

    date.addDays((kw-1)*7);

    return date;
}
