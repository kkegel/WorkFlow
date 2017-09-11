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
#include "process.h"

namespace Ui {
class ProcessDialog;
}

class ProcessDialog : public QDialog
{
    Q_OBJECT

public:

    explicit ProcessDialog(QWidget *parent = 0, Process* process);
    ~ProcessDialog();

private:

    Ui::ProcessDialog *ui;
    Process* process;

    void init_data();

private slots:

    void check_accept();
    void accept();

};

#endif // PROCESSDIALOG_H
