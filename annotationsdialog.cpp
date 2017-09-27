#include "annotationsdialog.h"
#include "ui_annotationsdialog.h"

AnnotationsDialog::AnnotationsDialog(Project* trans_project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnnotationsDialog)
{
    ui->setupUi(this);

    for(Process* p : trans_project->get_processes()){

        QWidget* w = new QWidget();
        w->setStyleSheet("background-color: #7a9bff");
        QLabel* head = new QLabel();
        head->setText(p->get_name());
        QLabel* body = new QLabel();
        body->setWordWrap(true);
        body->setText(p->get_annotation());
        QVBoxLayout* l = new QVBoxLayout(w);
        l->addWidget(head);
        l->setSpacing(0);
        l->setContentsMargins(0,0,0,0);

        ui->layout_content->addWidget(w);
        ui->layout_content->addWidget(body);
    }

}

AnnotationsDialog::~AnnotationsDialog()
{
    delete ui;
}
