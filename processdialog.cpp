#include "processdialog.h"
#include "ui_processdialog.h"

ProcessDialog::ProcessDialog(Process* process, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessDialog)
{
    ui->setupUi(this);

    this->process = process;

    if(process != nullptr){
        init_data();
    }

    connect(ui->pb_cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(ui->pb_save, SIGNAL(clicked(bool)), this, SLOT(check_accept()));
}

ProcessDialog::~ProcessDialog()
{
    delete ui;
}

void ProcessDialog::init_data(){

    ui->input_name->setText(process->get_name());
    ui->input_responsible->setText(process->get_responsible());
    ui->cw_start->setSelectedDate(process->get_start_time());
    ui->cw_end->setSelectedDate(process->get_end_time());

    if(process->get_state() != NULL){

        if(process->get_state().compare("COMPLETED_STATE") == 0){
            ui->cb_done->setChecked(true);
        }
        if(!process->get_state().compare("TEMPLATE_STATE") == 0){
            ui->cb_inwork->setChecked(true);
        }
    }

}

void ProcessDialog::check_accept(){

    bool check = true;

    try{
        if(ui->input_name->text().compare("") == 0 || ui->input_responsible->text().compare("") == 0){
            QErrorMessage* err = new QErrorMessage();
            err->showMessage("Eingabefelder dürfen nicht leer sein");
            check = false;
        }

        QDate start = ui->cw_start->selectedDate();
        QDate end = ui->cw_end->selectedDate();

        if(start.toJulianDay() >= end.toJulianDay()){
            QErrorMessage* err = new QErrorMessage();
            err->showMessage("Prozessdauer muss größer 0 Tage sein");
            check = false;
        }
    }catch(std::exception){
        check = false;
    }

    if(check){
        _m_accept();
    }else{
        QErrorMessage* err = new QErrorMessage();
        err->showMessage("Prozess konnte auf Grund von Fehlern nicht angelegt werden");
    }

}

void ProcessDialog::_m_accept(){

    QString hint = "";

    if(ui->cb_done->isChecked()){
        hint = "completed";
    }else{
        if(ui->cb_inwork->isChecked()){
            hint = "open";
        }else{
            hint = "template";
        }
    }

    QDate start = ui->cw_start->selectedDate().addDays(-1);
    QDate end = ui->cw_end->selectedDate();
    QString name = ui->input_name->text();
    QString responsible = ui->input_responsible->text();

    *process = Process(start, end, name, responsible, hint);

    accept();
}

