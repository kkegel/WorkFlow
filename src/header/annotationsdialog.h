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

#ifndef ANNOTATIONSDIALOG_H
#define ANNOTATIONSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QString>

#include "project.h"
#include "process_.h"

namespace Ui {
class AnnotationsDialog;
}

class AnnotationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnnotationsDialog(Project* trans_project, QWidget *parent = 0);
    ~AnnotationsDialog();

private:
    Ui::AnnotationsDialog *ui;
};

#endif // ANNOTATIONSDIALOG_H
