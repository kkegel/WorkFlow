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
