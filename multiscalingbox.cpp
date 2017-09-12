#include "multiscalingbox.h"

MultiScalingBox::MultiScalingBox(QDate front, QDate back, int width) :
    DateContainer(front, back, width)
{

}

ProjectItem* MultiScalingBox::get_shown_item_by_title(QString title){

    for(ProjectItem* item : items){
        if(item->get_title().compare(title) == 0){
            return item;
        }
    }

    return nullptr;
}

void MultiScalingBox::do_click_action(QString title){

}

QHBoxLayout* MultiScalingBox::get_layout_container(){

    return container;
}

std::vector<std::vector<QWidget*>>* MultiScalingBox::get_cells(){

    return &cells;
}

void MultiScalingBox::build_layout(){

    columns.clear();
    cells.clear();
    clear_layout(container);

    int shown_days = front_date.daysTo(back_date);

    for(int i = 0; i < shown_days + 3; i++){
        QVBoxLayout* col = new QVBoxLayout();
        container->addLayout(col);
        columns.push_back(col);
        std::vector<QWidget*> a;
        cells.push_back(a);
    }

    build_header();

    for(ProjectItem* item : items){
        if(item_is_shown(item)){

            QPushButton* title = new QPushButton(item->get_title());
            columns[0]->addWidget(title);
            cells[0].push_back(title);

            QDate c = QDate::fromJulianDay( item->get_start_time().toJulianDay());
            int col_counter = 1;

            while(c.toJulianDay() < item->get_end_time().toJulianDay()){
                QWidget* cell = new QWidget();
                switch (display_state_at_date(item, c)) {
                case 0:
                    cell->setStyleSheet("background-color: #e3f2fd");
                    break;
                case 2:
                    cell->setStyleSheet("background-color: #ffffff");
                    break;
                default:
                    cell->setStyleSheet("background-color: #546e7a");
                    break;
                }
                columns[col_counter]->addWidget(cell);
                cells[col_counter].push_back(cell);
                col_counter++;
                c.addDays(1);
            }

            QLabel* state = new QLabel();

            QString s_state = item->get_state();

            if(s_state.compare("OPEN_STATE") == 0){ //green
                state->setStyleSheet("background-color: #546e7a");
            }else if(s_state.compare("LATE_STATE") == 0){ //red
                state->setStyleSheet("background-color: #ff5252");
            }else if(s_state.compare("NEARLY_LATE_STATE") == 0){ //yellow
                state->setStyleSheet("background-color: #ffd740");
            }else if(s_state.compare("TEMPLATE_STATE")){ //grey
                state->setStyleSheet("background-color: #b0bec5");
            }else{
                state->setStyleSheet("background-color: #00ff00");//green
            }

            columns[columns.size()-2]->addWidget(state);
            cells[cells.size()-2].push_back(state);

            QPushButton* pb = new QPushButton("[]");
            columns[columns.size()-1]->addWidget(pb);
            cells[cells.size()-1].push_back(pb);

            rescale_layout();
        }
    }
}

void MultiScalingBox::build_header(){

    int shown_days = front_date.daysTo(back_date);
    int start_kw;

    int base = 0;
    int diff = shown_days/7; //number weeks (only full weeks)
    std::vector<int> displayed_days;

        while(base <= shown_days){
            displayed_days.push_back(base);
            base += diff;
        }

    QLabel* name = new QLabel("Bezeichnung");
    columns[0]->addWidget(name);
    cells[0].push_back(name);

    for(int i = 1; i < columns.size()-2; i++){

        QLabel* head_entry = new QLabel();

        if(displayed_days[0] == i-1){
            displayed_days.erase(displayed_days.begin());
            head_entry->setText("|"+QString(start_kw));
            start_kw++;
        }else{
            head_entry->setText("|");
        }

        head_entry->setAlignment(Qt::AlignLeft);
        columns[i]->addWidget(head_entry);
        cells[i].push_back(head_entry);

    }

    QLabel* state = new QLabel("Status");
    columns[columns.size()-2]->addWidget(state);
    cells[cells.size()-2].push_back(name);

    QLabel* open = new QLabel("Öffnen");
    columns[columns.size()-1]->addWidget(open);
    cells[cells.size()-1].push_back(open);

}

/*
 * breite der tabelle 80% des fenster
 */

void MultiScalingBox::rescale_layout(){

    container->setSpacing(0);

    for(QVBoxLayout* l : columns){
        l->setSpacing(0);
    }

    //column 1 max. 20%

    for(QWidget* w : cells[0]){
        w->setMaximumWidth((int)((double)width_pixel*0.2));
        ((QLabel*) w)->setMargin(0);

    }

    //bar columns max. 80/number %

    for(int i = 1; i < cells.size()-3; i++){
        for(QWidget* w : cells[i]){
            w->setMaximumWidth((0.8/(double)cells.size()-3) * width_pixel);
            w->setMinimumWidth((0.8/(double)cells.size()-3) * width_pixel);
            ((QLabel*) w)->setMargin(0);
        }
    }

    for(int i = 1; i <= 2; i++){
        for(QWidget* w : cells[cells.size()-i]){
            w->setMaximumWidth((int)((double)width_pixel*0.1));
            w->setMinimumWidth((int)((double)width_pixel*0.07));
        }
    }

}

void MultiScalingBox::add_date_based_item(ProjectItem* p){

    items.push_back(p);
}

void MultiScalingBox::remove_date_based_item(QString title){

    for(int i = 0; i < items.size(); i++){
        if(items[i]->get_title().compare(title) == 0){
            items.erase(items.begin()+i);
            break;
        }
    }
}

bool MultiScalingBox::item_is_shown(ProjectItem* p){

    if(QDateTime(p->get_end_time()).toSecsSinceEpoch() <
            QDateTime(QDate::currentDate()).toSecsSinceEpoch()){

        return false;
    }
    return true;
}

int MultiScalingBox::display_state_at_date(ProjectItem* p, QDate d){

    qint64 date_int = QDateTime(d).toSecsSinceEpoch();

    if(date_int >= QDateTime(p->get_end_time()).toSecsSinceEpoch()){
        return 2;
    }
    if(date_int > QDateTime(p->get_start_time()).toSecsSinceEpoch()){
        return 0;
    }
    return 1;
}


void MultiScalingBox::clear_all(){

    items.clear();
    clear_layout(container);
    columns.clear();
    cells.clear();

}

void MultiScalingBox::clear_layout(QLayout* layout){

    if(!layout){
        return;
    }
    while(auto item = layout->takeAt(0)){
        delete item->widget();
        clear_layout(item->layout());
    }
}
