#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLine>

#include <vector>

#include "project.h"
#include "process.h"

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:

    explicit UserDialog(std::vector<Project>* projects, QString user, QWidget *parent = 0);
    ~UserDialog();

private:

    Ui::UserDialog *ui;

    QString user;
    std::vector<Project>* projects;
    std::vector<std::vector<QString>> tasks;

    void init();
    void build_task_table();

};

#endif // USERDIALOG_H
