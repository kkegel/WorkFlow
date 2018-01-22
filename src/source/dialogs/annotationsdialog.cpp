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

#include "../../header/annotationsdialog.h"
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
