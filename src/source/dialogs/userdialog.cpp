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

#include "../../header/userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(std::vector<Project>* projects, QStringList user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    this->user = user;
    this->projects = projects;

    ui->setupUi(this);
    user.insert(user.begin(), " ");
    ui->cb_user->addItems(user);

    connect(ui->pb_close, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(ui->cb_user, SIGNAL(currentIndexChanged(int)), this, SLOT(init()));

}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::init(){

    clear_layout(ui->layout_content);
    tasks.clear();

    if(projects == nullptr){
        return;
    }

    build_task_table();

    for(int i = 0; i < 3; i++){
        QVBoxLayout* layout = new QVBoxLayout();
        for(std::vector<QString> l : tasks){
            QLabel* lbl = new QLabel();
            lbl->setText(l[i]);
            layout->addWidget(lbl);
        }
        ui->layout_content->addLayout(layout);
    }
}

void UserDialog::build_task_table(){

    QString user_s = ui->cb_user->currentText();

    for(int i = 0; i < projects->size(); i++){
        for(Process* p : projects->at(i).get_processes()){
            if(p->get_responsible().compare(user_s) == 0 && p->get_state().compare("COMPLETED_STATE") != 0){
                std::vector<QString> line;
                line.push_back(projects->at(i).get_id());
                line.push_back(p->get_name());
                line.push_back(p->get_end_time().toString());
                tasks.push_back(line);
            }
        }
    }
}

void UserDialog::clear_layout(QLayout* layout){

    if(!layout){
        return;
    }
    while(auto item = layout->takeAt(0)){
        delete item->widget();
        clear_layout(item->layout());
    }
}
