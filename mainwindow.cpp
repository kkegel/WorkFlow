#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    project_manager = ProjectManager();
    open_project = nullptr;

    init_layout_elements();
    state = new OverviewState();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_layout_elements(){

    connect(ui->pb_new, SIGNAL(clicked(bool)), this, SLOT(create_new_element()));
    connect(ui->pb_new_sector, SIGNAL(clicked(bool)), this, SLOT(load_new_sector()));
    connect(ui->pb_reload, SIGNAL(clicked(bool)), this, SLOT(reload_content_from_data());
}

void MainWindow::create_new_element(){
    state->create_new_element();
}

void MainWindow::load_new_sector(){

    //neuen bereich laden und msbox rescalen
}

void MainWindow::open_project_reading_mode(){

    QPushButton s = dynamic_cast<QPushButton*>(sender());
    open_project = project_manager.get_project_by_id(get_id_from_push_button(s));
    state->open_project_read(get_id_from_push_button(s));
}

void MainWindow::open_project_writing_mode(){

    if(!state->open_project_edit(open_project)){
        //fehlermeldung zeigen
    }
}

void MainWindow::close_project_writing_mode(){

    project_manager.save_project(open_project);
    state->open_project_read(open_project->get_id());

}

void MainWindow::open_project_overview(){

    open_project = nullptr;
    state->open_overview();
}

void MainWindow::reload_content_from_data(){

    project_manager.reload_all_projects();
    state->reload();
}

void MainWindow::connect_project_cells(){

    int i = 0;
    for(QWidget* w : cells->at(cells->size()-1)){

        if(i > 0){
            QPushButton p = dynamic_cast<QPushButton*>(w);
            connect(p, SIGNAL(clicked()), this, SLOT(open_project_reading_mode()));
        }
    }
}

void MainWindow::connect_process_cells(){

    int i = 0;
    for(QWidget* w : cells->at(cells->size()-1)){

        if(i > 0){
            QPushButton p = dynamic_cast<QPushButton*>(w);
            connect(p, SIGNAL(clicked()), this, SLOT(open_process_edit_dialog());
        }
    }
}

QString MainWindow::get_id_from_push_button(QPushButton* pb){

    int i;
    for(QWidget* w : cells->at(cells->size()-1)){
        if(i > 0){
            QPushButton p = dynamic_cast<QPushButton*>(w);
            if(p == w){
                return projects->at(i).get_id();
            }
        }
        i++;
    }
    return NULL;
}

void MainWindow::clear_layout(QLayout* layout){

    if(!layout){
        return;
    }
    while(auto item = layout->takeAt(0)){
        delete item->widget();
        clear_layout(item->layout());
    }
}

MainWindow::OverviewState::OverviewState(MainWindow* main) : WindowState(main){

   _main->ui->pb_edit->setEnabled(false);
   _main->ui->pb_reload->setEnabled(true);
   _main->ui->pb_new->setEnabled(true);
   _main->state->open_overview();
}

bool MainWindow::OverviewState::open_overview(){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    QDate front = first_day_of_kw(_main->ui->sb_from_kw->value(), _main->ui->sb_from_year->value());
    QDate back = first_day_of_kw(_main->ui->sb_to_kw->value(), _main->ui->sb_to_year->value());

    _main->ms_box = MultiScalingBox(front, back, _main->size().width());
    for(int i = 0; i < _main->projects->size(); i++){
        _main->ms_box.add_date_based_item(&(_main->projects->at(i)));
    }
    _main->ms_box.build_layout();
    _main->ui->barLayout->addLayout(_main->ms_box.get_layout_container());
    _main->connect_project_cells();
}

bool MainWindow::OverviewState::open_project_read(QString id){

    clear_layout(ui->barLayout);
    ms_box.clear_all();
    state = new ProjectReadState();
    state->open_project_read(id);

    return true;
}

bool MainWindow::OverviewState::create_new_element(){
    //create new project
}

bool MainWindow::OverviewState::reload(){
    state->open_overview();
}

MainWindow::ProjectReadState::ProjectReadState(MainWindow* main) : WindowState(main){

    ui->pb_edit->setEnabled(true);
    ui->pb_reload->setEnabled(true);
    ui->pb_new->setEnabled(false);

    ui->pb_edit->setText("bearbeiten");
    connect(ui->pb_edit, SIGNAL(clicked(bool)), this, SLOT(open_project_writing_mode()));
}

MainWindow::ProjectReadState::open_project_read(QString id){

    project_manager.load_active_projects();
    projects = project_manager.get_open_projects();

    Project* p = project_manager.get_project_by_id(id);

    for(Process* pc : p->get_processes()){
       ms_box.add_date_based_item(pc);
    }

    ms_box.build_layout();
    ui->barLayout->addLayout->(ms_box.get_layout_container());
    connect_cells();
}

bool MainWindow::ProjectReadState::open_overview(){

    clear_layout(ui->barLayout);
    ms_box.clear_all();
    state = new OverviewState();

    return true;
}

bool MainWindow::ProjectReadState::open_project_write(QString id){

    if(!project_manager.get_project_by_id(id)->is_writable()){
        return false;
    }
    project_manager.open_edit_mode(id);

    clear_layout(ui->barLayout);
    ms_box.clear_all();
    state = new ProjectWriteState();

    return true;
}

bool MainWindow::ProjectReadState::reload(){
    state->open_project_read(open_project->get_id());
}

MainWindow::ProjectWriteState::ProjectWriteState(MainWindow* main) : WindowState(main){

    ui->pb_new->setEnabled(true);
    ui->pb_reload->setEnabled(false);
    ui->pb_edit->setEnabled(true);

    ui->pb_edit->setText("speichern");
    connect(ui->pb_edit, SIGNAL(clicked(bool)), this, SLOT(close_project_writing_mode));

}

bool MainWindow::ProjectWriteState::open_project_read(){

}

bool MainWindow::ProjectWriteState::open_project_write(){

}

bool MainWindow::ProjectWriteState::create_new_element(){

}
