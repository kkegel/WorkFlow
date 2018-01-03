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
