#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDate>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QStringList>

#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QErrorMessage>
#include <QMessageBox>
#include <QFileDialog>

#include <vector>

#include "project.h"
#include "process_.h"
#include "projectitem.h"
#include "datecontainer.h"
#include "multiscalingbox.h"
#include "projectmanager.h"
#include "datahandler.h"
#include "state.h"
#include "userindex.h"
#include "commander.h"

#include "userdialog.h"
#include "helpdialog.h"
#include "createprojectdialog.h"
#include "processdialog.h"
#include "annotationsdialog.h"

#include "datelib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    class WindowState;
    class OverviewState;    //projects are shown as bars
    class ProjectReadState; //processes are shown as bars, not editable
    class ProjectWriteState;//processes are shown as bars, editable

    Ui::MainWindow *ui;

    ProjectManager project_manager;
    WindowState* state;
    MultiScalingBox ms_box;
    UserIndex user_index;
    Commander commander;

    Project* trans_project;
    Process* trans_process; //to handle data exchange with dialogs

    std::vector<std::vector<QWidget*>>* cells;
    std::vector<Project>* projects;

    QHBoxLayout* content_l;

    void _r_start();

    void load_base_layout();
    void init_layout_elements();
    void connect_project_cells(QString  mode);

    QString get_element_title_from_push_button(QPushButton* pb, std::vector<Project>* items);
    QString get_element_title_from_push_button(QPushButton* pb, std::vector<Process>* items);


    void clear_layout(QLayout* layout);

public slots:

    void create_new_element();
    void load_new_sector();
    void open_project_reading_mode();
    void open_project_writing_mode();
    void close_project_writing_mode();
    void open_project_overview();
    void open_process_edit_dialog();
    void reload_content_from_data();
    void handle_new_project();
    void edit_existing_project();
    void handle_new_process();
    void save_and_reload();
    void set_source();
    void handle_command();
    void show_info();
    void show_person_dialog();
    void show_today();
    void show_annotations();

};

class MainWindow::WindowState
{
public:

    WindowState(MainWindow* main){this->_main = main;}

    virtual bool open_overview() = 0;
    virtual bool open_project_read(QString id) = 0;
    virtual bool open_project_write(QString id) = 0;
    virtual bool create_new_element() = 0;
    virtual bool reload() = 0;

    MainWindow* _main;

};

class MainWindow::OverviewState : public WindowState
{
public:

    OverviewState(MainWindow* main);

    bool open_overview() override;
    bool open_project_write(QString id) override {return false;}
    bool open_project_read(QString id) override;
    bool create_new_element() override;
    bool reload() override;

};

class MainWindow::ProjectReadState : public WindowState
{
public:

    ProjectReadState(MainWindow* main);

    bool open_overview() override;
    bool open_project_write(QString id) override;
    bool open_project_read(QString id) override;
    bool create_new_element() override {return false;}
    bool reload() override;

};

class MainWindow::ProjectWriteState : public WindowState
{
public:

    ProjectWriteState(MainWindow* main);

    bool open_overview() override {return false;}
    bool open_project_read(QString id) override;
    bool open_project_write(QString id) override;
    bool create_new_element() override;
    bool reload() override;

};

#endif // MAINWINDOW_H
