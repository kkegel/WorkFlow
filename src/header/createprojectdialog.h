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

#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include <QDate>
#include <QErrorMessage>

#include <exception>
#include <vector>

#include "project.h"
#include "projectitem.h"

namespace Ui {
class CreateProjectDialog;
}

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:

    explicit CreateProjectDialog(Project* project, QWidget *parent = 0);
    ~CreateProjectDialog();

private:

    Ui::CreateProjectDialog *ui;
    Project* project;
    bool edit_state;
    QString old_id;

private slots:

    void check_accept();

    void _m_accept();
    void _m_reject();
};

#endif // CREATEPROJECTDIALOG_H
