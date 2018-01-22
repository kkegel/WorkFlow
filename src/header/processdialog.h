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

#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QDate>
#include <QString>
#include <QStringList>
#include <QErrorMessage>

#include "projectitem.h"
#include "process_.h"
#include "userindex.h"

namespace Ui {
class ProcessDialog;
}

class ProcessDialog : public QDialog
{
    Q_OBJECT

public:

    explicit ProcessDialog(Process* process, QStringList user, QWidget *parent = 0);
    ~ProcessDialog();

private:

    Ui::ProcessDialog *ui;
    Process* process;

    void init_data();

private slots:

    void check_accept();
    void _m_accept();

};

#endif // PROCESSDIALOG_H
