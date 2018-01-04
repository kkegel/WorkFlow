#include "../../header/processdialog.h"
#include "ui_processdialog.h"

ProcessDialog::ProcessDialog(Process* process, QStringList user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessDialog)
{
    ui->setupUi(this);

    this->process = process;

    ui->cb_responsible->addItems(user);

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
    ui->cb_responsible->setCurrentIndex(ui->cb_responsible->findData(process->get_responsible(), Qt::DisplayRole));
    ui->cw_start->setSelectedDate(process->get_start_time());
    ui->cw_end->setSelectedDate(process->get_end_time());
    ui->input_annotation->setPlainText(process->get_annotation());

    if(process->get_state() != NULL){

        if(process->get_state().compare("COMPLETED_STATE") == 0){
            ui->cb_done->setChecked(true);
            ui->cb_inwork->setChecked(true);
        }
        if(process->STARTED){
            ui->cb_inwork->setChecked(true);
        }
    }

}

void ProcessDialog::check_accept(){

    bool check = true;

    try{
        if(ui->input_name->text().compare("") == 0 || ui->cb_responsible->currentText().compare("") == 0){
            QErrorMessage* err = new QErrorMessage();
            err->showMessage("inputs must not be empty");
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
        err->showMessage("process could not be created - please remove your faults");
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

    QDate start = ui->cw_start->selectedDate();
    QDate end = ui->cw_end->selectedDate();
    QString name = ui->input_name->text();
    QString responsible = ui->cb_responsible->currentText();
    QString anno = ui->input_annotation->toPlainText();

    *process = Process(start, end, name, responsible, hint, anno);

    accept();
}

