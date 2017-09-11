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
    start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_layout_elements(){

    connect(ui->pb_new, SIGNAL(clicked(bool)), this, SLOT(create_new_element()));
    connect(ui->pb_new_sector, SIGNAL(clicked(bool)), this, SLOT(load_new_sector()));
    connect(ui->pb_reload, SIGNAL(clicked(bool)), this, SLOT(reload_content_from_data());
    connect(ui->pb_source, SIGNAL(clicked(bool)), this, SLOT(set_source()));
}

void MainWindow::start(){

    QDate front = first_day_of_kw(ui->sb_from_kw->value(), ui->sb_from_year->value());
    QDate back = first_day_of_kw(ui->sb_to_kw->value(), ui->sb_to_year->value());

    ms_box = MultiScalingBox(front, back, this->size().width());

    state = new OverviewState();

}

void MainWindow::create_new_element(){
    state->create_new_element();
}

void MainWindow::load_new_sector(){

    QDate front = first_day_of_kw(ui->sb_from_kw->value(), ui->sb_from_year->value());
    QDate back = first_day_of_kw(ui->sb_to_kw->value(), ui->sb_to_year->value());

    ms_box.set_front_date(front);
    ms_box.set_back_date(back);

    state->reload();
}

void MainWindow::open_project_reading_mode(){

    QPushButton* s = dynamic_cast<QPushButton*>(sender());
    open_project = project_manager.get_project_by_id(get_element_title_from_push_button(s, projects));
    state->open_project_read(get_elemt_title_from_push_button(s, projects));
}

void MainWindow::open_project_writing_mode(){

    if(!state->open_project_write(open_project)){
        QErrorMessage* err = new QErrorMessage("Kein Zugriff, da ein anderer PC das Projekt bereits im Schreibmodus geöffnet hat.");
        err->show();
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

void MainWindow::handle_new_project(){

    project_manager.save_project((Project*)trans_pi);
    project_manager.reload_all_projects();
    state->reload();
}

void MainWindow::handle_new_process(){

    open_project->add_process((Process)*trans_pi);
    save_and_reload();
}

void MainWindow::save_and_reload(){

    project_manager.save_project(open_project);
    state->reload();
}

void MainWindow::set_source(){

    QString source = QFileDialog::getOpenFileName(this, ("Index auswählen"),
                                                     "/",
                                                     ("XML-Datei (*.xml)"));
    if(source != nullptr && !source.isNull()){
        project_manager.set_source(source);
    }
}

void MainWindow::open_process_edit_dialog(){

    QPushButton* s = dynamic_cast<QPushButton*>(sender());
    trans_pi = open_project->get_process_by_name(get_element_title_from_push_button(s, open_project->get_processes_p()));

    ProcessDialog* pd = new ProcessDialog(trans_pi);
    pd->show();
    connect(pd, SIGNAL(accepted()), this, SLOT(save_and_reload()));
}

void MainWindow::connect_project_cells(QString mode){

    int i = 0;
    for(QWidget* w : cells->at(cells->size()-1)){

        if(i > 0){
            QPushButton p = dynamic_cast<QPushButton*>(w);

            if(mode.compare("overview") == 0){
                connect(p, SIGNAL(clicked(bool)), this, SLOT(open_project_reading_mode()));
            }else if(mode.compare("read") == 0){
                connect(p, SIGNAL(clicked(bool)), this, SLOT(open_project_writing_mode()));
            }else if(mode.compare("write") == 0){
                connect(p, SIGNAL(clicked(bool)), this, SLOT(open_process_edit_dialog()));
            }
        }
    }
}

QString MainWindow::get_element_title_from_push_button(QPushButton* pb, std::vector<ProjectItem>* items){

    int i;
    for(QWidget* w : cells->at(cells->size()-1)){
        if(i > 0){
            QPushButton* p = dynamic_cast<QPushButton*>(w);
            if(p == w){
                return items->at(i).get_title();
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

/*
 * WindowState - state machine:
 */

MainWindow::OverviewState::OverviewState(MainWindow* main) : WindowState(main){

   _main->ui->pb_edit->setEnabled(false);
   _main->ui->pb_reload->setEnabled(true);
   _main->ui->pb_new->setEnabled(true);
   _main->state->open_overview();
}

bool MainWindow::OverviewState::open_overview(){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    for(int i = 0; i < _main->projects->size(); i++){
        _main->ms_box.add_date_based_item(&(_main->projects->at(i)));
    }
    _main->ms_box.build_layout();
    _main->ui->barLayout->addLayout(_main->ms_box.get_layout_container());
    _main->connect_project_cells("overview");
}

bool MainWindow::OverviewState::open_project_read(QString id){

    _main->clear_layout(_main->ui->barLayout);
    _main->ms_box.clear_all();
    _main->state = new ProjectReadState();
    _main->state->open_project_read(id);

    return true;
}

bool MainWindow::OverviewState::create_new_element(){

    _main->trans_pi = new Project();
    CreateProjectDialog* cpd = new CreateProjectDialog(trans_pi);
    cpd->show();
    connect(cpd, SIGNAL(accepted()), _main, SLOT(handle_new_project()));

    return true;
}

bool MainWindow::OverviewState::reload(){
    _main->state->open_overview();
    return true;
}

MainWindow::ProjectReadState::ProjectReadState(MainWindow* main) : WindowState(main){

    _main->ui->pb_edit->setEnabled(true);
    _main->ui->pb_reload->setEnabled(true);
    _main->ui->pb_new->setEnabled(false);

    _main->ui->pb_edit->setText("bearbeiten");
    connect(_main->ui->pb_edit, SIGNAL(clicked(bool)), _main, SLOT(open_project_writing_mode()));
}

MainWindow::ProjectReadState::open_project_read(QString id){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    Project* p = _main->project_manager.get_project_by_id(id);
    _main->open_project = p;

    for(Process* pc : p->get_processes()){
       _main->ms_box.add_date_based_item(pc);
    }

    _main->ms_box.build_layout();
    _main->ui->barLayout->addLayout->(_main->ms_box.get_layout_container());
    _main->connect_project_cells("read");
}

bool MainWindow::ProjectReadState::open_overview(){

    _main->clear_layout(_main->ui->barLayout);
    _main->ms_box.clear_all();
    _main->state = new OverviewState();

    return true;
}

bool MainWindow::ProjectReadState::open_project_write(QString id){

    if(!_main->project_manager.get_project_by_id(id)->is_writable()){
        return false;
    }
    _main->project_manager.open_edit_mode(id);

    _main->clear_layout(ui->barLayout);
    _main->ms_box.clear_all();
    _main->state = new ProjectWriteState();

    return true;
}

bool MainWindow::ProjectReadState::reload(){
    _main->state->open_project_read(_main->open_project->get_id());
    return true;
}

MainWindow::ProjectWriteState::ProjectWriteState(MainWindow* main) : WindowState(main){

    _main->ui->pb_new->setEnabled(true);
    _main->ui->pb_reload->setEnabled(false);
    _main->ui->pb_edit->setEnabled(true);

    _main->ui->pb_edit->setText("speichern");
    connect(_main->ui->pb_edit, SIGNAL(clicked(bool)), _main, SLOT(close_project_writing_mode));

}

bool MainWindow::ProjectWriteState::open_project_read(){

    _main->clear_layout(ui->barLayout);
    _main->ms_box.clear_all();
    _main->state = new ProjectReadState(_main->open_project->get_id());

    return true;
}

bool MainWindow::ProjectWriteState::open_project_write(){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    Project* p = _main->project_manager.get_project_by_id(id);

    for(Process* pc : p->get_processes()){
       _main->ms_box.add_date_based_item(pc);
    }

    _main->ms_box.build_layout();
    _main->ui->barLayout->addLayout->(_main->ms_box.get_layout_container());
    _main->connect_project_cells("write");

    return true;
}

bool MainWindow::ProjectWriteState::create_new_element(){

    _main->trans_pi = new Process();
    ProcessDialog* pd = new ProcessDialog(_main->trans_pi);
    pd->show();
    connect(pd, SIGNAL(accepted()), _main, SLOT(handle_new_process()));

    return true;
}

bool MainWindow::ProjectWriteState::reload(){
    _main->state->open_project_write(_main->open_project->get_id());
    return true;
}
