#ifndef DATECONTAINER_H
#define DATECONTAINER_H

#include <QString>
#include <QDate>
#include <QDateTime>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <vector>

#include "project.h"
#include "process.h"
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

private:

    QDate front_date;
    QDate back_date;

    int width_pixel;

};

#endif // DATECONTAINER_H
