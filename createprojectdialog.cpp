#include "createprojectdialog.h"
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

    if(project->get_id().compare("") != 0){
        ui->input_id->setEnabled(false);
    }

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
            err->showMessage("Projektdauer muss größer 0 Tage sein");
            check = false;
        }
    }catch(std::exception){
        check = false;
    }

    if(check){
        _m_accept();
    }else{
        QErrorMessage* err = new QErrorMessage();
        err->showMessage("Projekt konnte auf Grund von Fehlern nicht angelegt werden");
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

    *project = Project(start, end, id, true, *(project->get_processes_p()), project->get_state_hint());

    accept();
}
