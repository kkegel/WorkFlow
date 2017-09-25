#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(std::vector<Project>* projects, QString user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    this->user = user;
    this->projects = projects;
    ui->setupUi(this);
    init();
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::init(){

    connect(ui->pb_close, SIGNAL(clicked(bool)), this, SLOT(accept()));

    ui->lbl_user->setText(user);

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

    for(int i = 0; i < projects->size(); i++){
        for(Process* p : projects->at(i).get_processes()){
            if(p->get_responsible().compare(user) == 0 && p->get_state().compare("COMPLETED_STATE") != 0){
                std::vector<QString> line;
                line.push_back(projects->at(i).get_id());
                line.push_back(p->get_name());
                line.push_back(p->get_end_time().toString());
                tasks.push_back(line);
            }
        }
    }
}
