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

#ifndef MULTISCALINGBOX_H
#define MULTISCALINGBOX_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

#include <vector>
#include <math.h>

#include "datecontainer.h"
#include "projectitem.h"
#include "process_.h"
#include "project.h"

class MultiScalingBox : public DateContainer
{
public:

    MultiScalingBox(QDate front, QDate back, int width);
    MultiScalingBox() : DateContainer(){}

    ProjectItem* get_shown_item_by_title(QString title);

    void do_click_action(QString title);

    QHBoxLayout* get_layout_container();
    std::vector<std::vector<QWidget*>>* get_cells();
    std::vector<QVBoxLayout*>* get_columns();

    void build_layout(QString mode = "_t_over");
    void rescale_layout();

    void add_date_based_item(ProjectItem* p);
    void remove_date_based_item(QString title);

    void clear_all();

private:

    bool item_is_shown(ProjectItem* p);

    /**
     * @brief display_state_at_date
     * @return
     *
     * 0 date before start
     * 1 is displayed
     * 2 date after end
     */

    int display_state_at_date(ProjectItem *p, QDate d);

    /**
     * @brief build_layout
     * @param mode
     *
     */

    void clear_layout(QLayout* layout);

    void build_header();

    std::vector<ProjectItem*> items;

    QHBoxLayout* container;
    std::vector<QVBoxLayout*> columns;
    std::vector<std::vector<QWidget*>> cells;

};

#endif // MULTISCALINGBOX_H
