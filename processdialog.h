#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QDate>
#include <QString>
#include <QErrorMessage>

#include "projectitem.h"
#include "process_.h"

namespace Ui {
class ProcessDialog;
}

class ProcessDialog : public QDialog
{
    Q_OBJECT

public:

    explicit ProcessDialog(Process* process, QWidget *parent = 0);
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
