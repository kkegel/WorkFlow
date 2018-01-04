#include "../../header/storedialog.h"
#include "ui_storedialog.h"

StoreDialog::StoreDialog(ProjectManager* pm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StoreDialog)
{
    ui->setupUi(this);
    this->pm = pm;
    init();
}

StoreDialog::~StoreDialog()
{
    delete ui;
}

void StoreDialog::init(){

    connect(ui->pb_close, SIGNAL(clicked(bool)), this, SLOT(accept()));

    pm->load_stored_projects();
    p_store = pm->get_stored_projects();

    QVBoxLayout* names = new QVBoxLayout();
    QVBoxLayout* btns = new QVBoxLayout();

    int i = 0;
    for(Project p : *p_store){
        QLabel* name = new QLabel(p.get_id());
        names->addWidget(name);
        QPushButton* btn = new QPushButton();
        btn->setText("restore");
        btn->setObjectName(QString::number(i));
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(restore()));
        btns->addWidget(btn);
        buttons.push_back(btn);
        i++;
    }

    ui->layout_content->addLayout(names);
    ui->layout_content->addLayout(btns);

}

void StoreDialog::restore(){

    QPushButton* s = dynamic_cast<QPushButton*>(sender());
    int i = s->objectName().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "action required", "are you sure to restore the selected project?",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        p_store->at(i).set_open();
        pm->save_project(&p_store->at(i));
        accept();
    }

}
