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

#include "../../header/createprojectdialog.h"
#include "ui_createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(Project* project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);

    this->project = project;

    connect(ui->pb_cancel, SIGNAL(clicked(bool)), this, SLOT(_m_reject()));
    connect(ui->pb_save, SIGNAL(clicked(bool)), this, SLOT(check_accept()));

    ui->input_id->setText(project->get_id());
    ui->cw_start->setSelectedDate(project->get_start_time());
    ui->cw_end->setSelectedDate(project->get_end_time());
    edit_state = false;

    if(project->get_id().compare("") != 0){
        //ui->input_id->setEnabled(false);
        //ui->cw_start->setEnabled(false);
        //ui->cw_end->setEnabled(false);
        //ui->pb_save->setEnabled(false);
        edit_state = true;
    }

    old_id = QString(project->get_id());

}

CreateProjectDialog::~CreateProjectDialog()
{
    delete ui;
}

void CreateProjectDialog::check_accept(){

    bool check = true;

    try{
        if(ui->input_id->text().compare("") == 0){
            QErrorMessage* err = new QErrorMessage();
            err->showMessage("Projektkennung ungültig");
            check = false;
        }

        QDate start = ui->cw_start->selectedDate();
        QDate end = ui->cw_end->selectedDate();

        if(start.toJulianDay() > end.toJulianDay()){
            QErrorMessage* err = new QErrorMessage();
            err->showMessage("duration has to be more than 0 days");
            check = false;
        }
    }catch(std::exception){
        check = false;
    }

    if(check){
        _m_accept();
    }else{
        QErrorMessage* err = new QErrorMessage();
        err->showMessage("project could not be crated - please remove your faults");
    }

}

void CreateProjectDialog::_m_reject(){
    project = nullptr;
    reject();
    destroy(true);
}

void CreateProjectDialog::_m_accept(){

    QString id = ui->input_id->text();
    QDate start = ui->cw_start->selectedDate();
    QDate end = ui->cw_end->selectedDate();

    if(edit_state && old_id.compare(id) != 0){
        id = "#?#" + old_id + "#!#" + id;
    }

    *project = Project(start, end, id, true, *(project->get_processes_p()), project->get_state_hint());

    accept();
}
