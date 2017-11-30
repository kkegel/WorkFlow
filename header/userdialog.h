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
