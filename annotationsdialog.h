#ifndef ANNOTATIONSDIALOG_H
#define ANNOTATIONSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QVBoxLayout>
#include <QString>

#include "project.h"
#include "process.h"

namespace Ui {
class AnnotationsDialog;
}

class AnnotationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnnotationsDialog(Project* trans_project, QWidget *parent = 0);
    ~AnnotationsDialog();

private:
    Ui::AnnotationsDialog *ui;
};

#endif // ANNOTATIONSDIALOG_H
