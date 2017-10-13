#ifndef DATELIB_H
#define DATELIB_H

#include <QDate>
#include <QDateTime>

QDate first_day_of_kw(int kw, int year);
bool is_valid_difference(QDate start, QDate end);

#endif // DATELIB_H
