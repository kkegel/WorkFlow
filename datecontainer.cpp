#include "datecontainer.h"

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
