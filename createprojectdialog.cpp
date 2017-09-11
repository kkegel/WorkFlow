#include "createprojectdialog.h"
#include "ui_createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent, Project* project) :
    QDialog(parent),
    ui(new Ui::CreateProjectDialog)
{
    ui->setupUi(this);

    this->project = project;

    connect(ui->pb_cancel, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(ui->pb_accept, SIGNAL(clicked(bool)), this, SLOT(check_accept()));
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
            err->showMessage("Auftragsnummer ungültig");
            check = false;
        }

        QDate start = ui->cw_start->selectedDate();
        QDate end = ui->cw_end->selectedDate();

        if(start.toJulianDay() <= end.toJulianDay()){
            QErrorMessage* err = new QErrorMessage();
            err->showMessage("Auftragsdauer muss größer 0 Tage sein");
            check = false;
        }
    }catch(exception){
        check = false;
    }

    if(check){
        accept();
    }else{
        QErrorMessage* err = new QErrorMessage();
        err->showMessage("Auftrag konnte auf Grund Fehler nicht angelegt werden");
    }

}

void CreateProjectDialog::reject(){
    project = nullptr;
}

void CreateProjectDialog::accept(){

    QString id = ui->input_id->text();
    QDate start = ui->cw_start->selectedDate();
    QDate end = ui->cw_end->selectedDate();

    std::vector<Process> processes;

    *project = Project(start, end, id, true, processes, "open");
}
