#ifndef MULTISCALINGBOX_H
#define MULTISCALINGBOX_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <vector>
#include <math.h>

#include "datecontainer.h"
#include "projectitem.h"
#include "process.h"
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

    void build_layout();
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
