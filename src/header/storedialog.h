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

#ifndef STOREDIALOG_H
#define STOREDIALOG_H

#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <vector>

#include "project.h"
#include "projectmanager.h"

namespace Ui {
class StoreDialog;
}

class StoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StoreDialog(ProjectManager* pm, QWidget *parent = 0);
    ~StoreDialog();

private:

    Ui::StoreDialog *ui;

    ProjectManager* pm;

    std::vector<Project>* p_store;
    std::vector<QPushButton*> buttons;

    void init();

private slots:

    void restore();

};

#endif // STOREDIALOG_H
