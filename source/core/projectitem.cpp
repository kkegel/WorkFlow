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

