#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QDateTime>
#include <QString>

#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

#include <vector>

#include "project.h"
#include "process.h"
#include "projectitem.h"
#include "datecontainer.h"
#include "multiscalingbox.h"
#include "projectmanager.h"
#include "datahandler.h"
#include "state.h"

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
    Project* open_project;

    std::vector<std::vector<QWidget*>>* cells;
    std::vector<Project>* projects;

    void load_base_layout();
    void init_layout_elements();
    void connect_project_cells();
    void connect_process_cells();
    QString get_id_from_push_button(QPushButton* pb);

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
};

class MainWindow::WindowState
{
public:

    WindowState(MainWindow* main){this->_main = main;}

    bool open_overview(){return false;}
    bool open_project_read(QString id){return false;}
    bool open_project_edit(QString id){return false;}
    bool create_new_element(){return false;}
    bool reload(){return false;}

    MainWindow* _main;

};

class MainWindow::OverviewState : public WindowState
{
public:

    OverviewState(MainWindow* main);

    bool open_overview();
    bool open_project_read(QString id);
    bool create_new_element();
    bool reload();

};

class MainWindow::ProjectReadState : public WindowState
{
public:

    ProjectReadState(MainWindow* main);

    bool open_overview();
    bool open_project_write(QString id);
    bool open_project_read(QString id);
    bool reload();

};

class MainWindow::ProjectWriteState : public WindowState
{
public:

    ProjectWriteState(MainWindow* main);

    bool open_project_read(QString id);
    bool open_project_write(QString id);
    bool create_new_element();

};

#endif // MAINWINDOW_H
