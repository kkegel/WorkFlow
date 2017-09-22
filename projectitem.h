#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QDate>
#include <QString>
#include <state.h>

/**
 * @brief The ProjectItem class
 *
 * a project item is either a Project or a Process
 * this generalization is importent for layout handling at
 * the front end.
 */

class ProjectItem
{
public:

    ProjectItem(QDate start_time, QDate end_time);
    ProjectItem(){}

    QDate get_start_time();

    QDate get_end_time();

    virtual QString get_state() = 0;
    virtual QString get_title() = 0;

    QDate START_TIME;
    QDate END_TIME;

private:


};

#endif // PROJECTITEM_H
