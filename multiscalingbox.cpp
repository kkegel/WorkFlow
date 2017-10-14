#include "multiscalingbox.h"

MultiScalingBox::MultiScalingBox(QDate front, QDate back, int width) :
    DateContainer(front, back, width)
{
    container = new QHBoxLayout();
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

std::vector<QVBoxLayout*>* MultiScalingBox::get_columns(){

    return &columns;
}

void MultiScalingBox::build_layout(QString mode){

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

    bool first = true;
    for(ProjectItem* item : items){
        if(true/*item_is_shown(item)*/){

            QLabel* title = new QLabel(item->get_title());

            QLabel* time = new QLabel();
            time->setText(item->get_start_time().toString("dd.MM.yy") + " - " +
                           item->get_end_time().toString("dd.MM.yy"));

            QWidget* w = new QWidget();
            w->setMinimumHeight(60);
            QVBoxLayout* h = new QVBoxLayout(w);
            h->setSpacing(0);
            h->addWidget(title);
            h->addWidget(time);

            if(mode.compare("_f_over") == 0 && !first){
                Process* p = dynamic_cast<Process*>(item);
                QLabel* resp = new QLabel(p->get_responsible());
                h->addWidget(resp);
            }

            columns[0]->addWidget(w);
            cells[0].push_back(w);

            QDate c = front_date;
            int col_counter = 1;

            while(c.toJulianDay() < back_date.toJulianDay()){

                QFrame* cell = new QFrame();
                cell->setMinimumHeight(60);

                switch (display_state_at_date(item, c)) {
                case 0:
                    cell->setStyleSheet("background-color: #6dcaff"); //dabei
                    break;
                case 2:
                    cell->setStyleSheet("background-color: #e8eaf6"); //danach
                    break;
                default:
                    cell->setStyleSheet("background-color: #e0f2f1"); //davor
                    break;
                }

                if(mode.compare("_t_over") == 0){
                    Project* p = dynamic_cast<Project*>(item);
                    if(p->is_dead_line(c)){
                        cell->setStyleSheet("background-color: #1877b5");
                    }
                }

                if(c.toJulianDay() == QDate::currentDate().toJulianDay()){
                    cell->setFrameShape(QFrame::Box);
                    cell->setLineWidth(2);
                }

                columns[col_counter]->addWidget(cell);
                cells[col_counter].push_back(cell);
                col_counter++;
                c = c.addDays(1);
            }

            QLabel* state = new QLabel();
            state->setMinimumHeight(60);

            QString s_state = item->get_state();

            if(s_state.compare("OPEN_STATE") == 0){
                state->setStyleSheet("background-color: #546e7a");
            }else if(s_state.compare("LATE_STATE") == 0){ //red
                state->setStyleSheet("background-color: #ff5252");
            }else if(s_state.compare("NEARLY_LATE_STATE") == 0){ //yellow
                state->setStyleSheet("background-color: #ffd740");
            }else if(s_state.compare("TEMPLATE_STATE") == 0){ //grey
                state->setStyleSheet("background-color: #b0bec5");
            }else{
                state->setStyleSheet("background-color: #9ccc65");//green
            }

            columns[columns.size()-2]->addWidget(state);
            cells[cells.size()-2].push_back(state);

            QPushButton* pb = new QPushButton("[]");
            pb->setObjectName(item->get_title());
            pb->setMinimumHeight(60);
            columns[columns.size()-1]->addWidget(pb);
            cells[cells.size()-1].push_back(pb);

            if(first && mode.compare("_f_over") == 0){
                w->setStyleSheet("background-color : #bbbbbb");
                //pb->setEnabled(false);
                pb->setText("[[]]");
                first = false;
            }else if(mode.compare("_t_over") == 0){
                Project* p = dynamic_cast<Project*>(item);
                if(p->get_processes().size() == 0){
                    state->setStyleSheet("background-color: #b0bec5");
                }
            }

            rescale_layout();
        }
    }
}

void MultiScalingBox::build_header(){

    int shown_days = front_date.daysTo(back_date);
    int start_kw = front_date.weekNumber();

    int base = 0;
    int diff = shown_days/7; //number weeks (only full weeks)
    std::vector<int> displayed_days;

        while(base <= shown_days){
            displayed_days.push_back(base);
            base += diff;
        }

    QLabel* name = new QLabel(" ");
    columns[0]->addWidget(name);
    cells[0].push_back(name);

    int s = columns.size();
    for(int i = 1; i < columns.size()-2; i++){

        QLabel* head_entry = new QLabel();
        QString head_text = "";

        if(i % 7 == 1){
            //displayed_days.erase(displayed_days.begin());
            head_text = "|" + QString::number(start_kw);
            start_kw++;
        }else{
            if(shown_days <= 28){
                head_text = "|";
            }else{
                head_text = "";
            }
        }

        head_entry->setText(head_text);
        head_entry->setAlignment(Qt::AlignLeft);
        columns[i]->addWidget(head_entry);
        cells[i].push_back(head_entry);

    }

    QLabel* state = new QLabel("Status");
    state->setAlignment(Qt::AlignCenter);
    columns[columns.size()-2]->addWidget(state);
    cells[cells.size()-2].push_back(name);

    QLabel* open = new QLabel("Öffnen");
    open->setAlignment(Qt::AlignCenter);
    columns[columns.size()-1]->addWidget(open);
    cells[cells.size()-1].push_back(open);

}

/*
 * breite der tabelle 80% des fenster
 */

void MultiScalingBox::rescale_layout(){

    container->setSpacing(2);

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

    if(p->get_state().compare("STOCKED_STATE")){
        return false;
    }
    return true;
}

int MultiScalingBox::display_state_at_date(ProjectItem* p, QDate d){

    qint64 date_int = d.toJulianDay();

    if(date_int > p->get_end_time().toJulianDay()){
        return 2;//nach ende
    }
    if(date_int >= p->get_start_time().toJulianDay()){
        return 0;//in zeit
    }
    return 1;//davor
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
