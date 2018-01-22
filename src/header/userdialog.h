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

#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLine>

#include <vector>

#include "project.h"
#include "process_.h"

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:

    explicit UserDialog(std::vector<Project>* projects,
                        QStringList user, QWidget *parent = 0);
    ~UserDialog();

private:

    Ui::UserDialog *ui;

    QStringList user;
    std::vector<Project>* projects;
    std::vector<std::vector<QString>> tasks;

    void build_task_table();
    void clear_layout(QLayout* layout);

private slots:

    void init();

};

#endif // USERDIALOG_H
