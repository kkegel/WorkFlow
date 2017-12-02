#include "../../header/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    project_manager = ProjectManager();

    trans_project = nullptr;
    trans_process = nullptr;
    user_index = UserIndex(project_manager.get_data_handler());

    QWidget* scrollContainer = ui->scrollContent;
    QVBoxLayout* scrollContentL = new QVBoxLayout(scrollContainer);
    barLayout = new QHBoxLayout();
    scrollContentL->addLayout(barLayout);
    QSpacerItem* spi = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    spi->setAlignment(Qt::AlignVCenter);
    scrollContentL->addItem(spi);
    scrollContainer->setLayout(scrollContentL);

    init_layout_elements();
    _r_start();
    //qApp->processEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_layout_elements(){

    connect(ui->pb_new, SIGNAL(clicked(bool)), this, SLOT(create_new_element()));
    connect(ui->pb_new_sector, SIGNAL(clicked(bool)), this, SLOT(load_new_sector()));
    connect(ui->pb_reload, SIGNAL(clicked(bool)), this, SLOT(reload_content_from_data()));
    connect(ui->pb_source, SIGNAL(clicked(bool)), this, SLOT(set_source()));
    connect(ui->pb_back, SIGNAL(clicked(bool)), this, SLOT(open_project_overview()));
    connect(ui->pb_today, SIGNAL(clicked(bool)), this, SLOT(show_today()));
    connect(ui->pb_person, SIGNAL(clicked(bool)), this, SLOT(show_person_dialog()));
    connect(ui->pb_annotation, SIGNAL(clicked(bool)), this, SLOT(show_annotations()));
    connect(ui->pb_store, SIGNAL(clicked(bool)), this, SLOT(show_store()));
    connect(ui->pb_to_store, SIGNAL(clicked(bool)), this, SLOT(store_current()));
}

void MainWindow::_r_start(){

    //qApp->processEvents();

    QDate front = first_day_of_kw(ui->sb_from_kw->value(), ui->sb_from_year->value());
    QDate back = first_day_of_kw(ui->sb_to_kw->value(), ui->sb_to_year->value());

    ms_box = MultiScalingBox(front, back, this->size().width());
    cells = ms_box.get_cells();

    state = new OverviewState(this);

}

void MainWindow::create_new_element(){
    if(check_input()){
    state->create_new_element();
    }
}

void MainWindow::load_new_sector(){

    if(check_input()){
    QDate front = first_day_of_kw(ui->sb_from_kw->value(), ui->sb_from_year->value());
    QDate back = first_day_of_kw(ui->sb_to_kw->value(), ui->sb_to_year->value());

    ms_box.set_front_date(front);
    ms_box.set_back_date(back);

    state->reload();
    }
}

void MainWindow::open_project_reading_mode(){

    if(check_input()){
    QPushButton* s = dynamic_cast<QPushButton*>(sender());
    trans_project = project_manager.get_project_by_id(s->objectName());
    state->open_project_read(trans_project->get_id());
    }
}

void MainWindow::open_project_writing_mode(){

    reload_content_from_data();
    if(check_input()){
    if(!state->open_project_write(trans_project->get_id())){
        QErrorMessage* err = new QErrorMessage();
        err->showMessage("Kein Zugriff, da ein anderer PC das Projekt bereits im Schreibmodus geöffnet hat.");
    }
    }
}

void MainWindow::close_project_writing_mode(){

    if(check_input()){
    trans_project->set_writeable(true);
    project_manager.save_project(trans_project);
    state->open_project_read(trans_project->get_id());
    }
}

void MainWindow::open_project_overview(){

    if(check_input()){
    trans_project = nullptr;
    state->open_overview();
    }
}

void MainWindow::reload_content_from_data(){

    if(check_input()){
    project_manager.reload_all_projects();
    state->reload();
    }
}

void MainWindow::handle_new_project(){

    if(check_input()){
    project_manager.save_project(trans_project);
    project_manager.reload_all_projects();
    state->reload();
    }
}

void MainWindow::edit_existing_project(){

    CreateProjectDialog* cpd = new CreateProjectDialog(trans_project);
    cpd->show();
    connect(cpd, SIGNAL(accepted()), this, SLOT(handle_new_project()));
}

void MainWindow::handle_new_process(){

    if(check_input()){
    trans_project->add_process(*trans_process);
    save_and_reload();
    }
}

void MainWindow::save_and_reload(){
    
    if(check_input()){
    project_manager.save_project(trans_project);
    state->reload();
    }
}

void MainWindow::reload_view(){
    reload_content_from_data();
    state->reload();
}

void MainWindow::show_person_dialog(){
    UserDialog *ud = new UserDialog(projects, user_index.to_string_list());
    ud->show();
}

void MainWindow::show_annotations(){
    AnnotationsDialog* ad = new AnnotationsDialog(trans_project);
    ad->show();
}

bool MainWindow::check_input(){
 
    if(is_valid_difference(first_day_of_kw(ui->sb_from_kw->value(), ui->sb_from_year->value()),
                           first_day_of_kw(ui->sb_to_kw->value(), ui->sb_to_year->value()))){
        return true;
    }
    QErrorMessage* err = new QErrorMessage();
    err->showMessage("Anzeigeparameter sind fehlerhaft. Ansicht kann nicht aktualisiert werden");
    return false;
}

void MainWindow::show_store(){

    StoreDialog* sd = new StoreDialog(&project_manager);
    sd->show();
    connect(sd, SIGNAL(accepted()), this, SLOT(reload_view()));
    connect(sd, SIGNAL(recjected()), this, SLOT(reload_view()));

}

void MainWindow::store_current(){

      QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "action required", "are you sure to move the current project to the store?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          project_manager.close_edit_mode(trans_project->get_id());
          trans_project->move_to_stock();
          project_manager.save_project(trans_project);
          state->open_project_read(trans_project->get_id());
          state->open_overview();
      }

}

void MainWindow::show_today(){

    if(ui->pb_reload->isEnabled()){

        int sw = QDate::currentDate().addDays(-7).weekNumber();
        int sj = QDate::currentDate().addDays(-7).year();
        int ew = QDate::currentDate().addDays(12).weekNumber();
        int ej = QDate::currentDate().addDays(12).year();

        ui->sb_from_kw->setValue(sw); ui->sb_from_year->setValue(sj);
        ui->sb_to_kw->setValue(ew); ui->sb_to_year->setValue(sj);
        ms_box.set_front_date(first_day_of_kw(sw, sj));
        ms_box.set_back_date(first_day_of_kw(ew, ej));
        state->reload();

    } else{

        QErrorMessage* em = new QErrorMessage();
        em->showMessage("bitte vorerst speichern");
    }
}

void MainWindow::set_source(){

    QString source = QFileDialog::getOpenFileName(this, ("Index auswählen"),
                                                     "/",
                                                     ("XML-Datei (*.xml)"));
    if(source != nullptr && !source.isNull()){
        project_manager.set_source(source);
        QErrorMessage* em = new QErrorMessage();
        em->showMessage("Änderungen wurden übernommen. Bitte starten sie das Programm neu. "
                        "Sollte es zu unerwartetem Verhalten kommen, wenden sie sich bitte an die zuständige Fachperson.");

    }
}

void MainWindow::open_process_edit_dialog(){

    QPushButton* s = dynamic_cast<QPushButton*>(sender());
    trans_process = trans_project->get_process_by_name(s->objectName());

    ProcessDialog* pd = new ProcessDialog(trans_process, user_index.to_string_list());
    pd->show();
    connect(pd, SIGNAL(accepted()), this, SLOT(save_and_reload()));
}

void MainWindow::connect_project_cells(QString mode){

    int top = cells->size()-1;
    int col = cells->at(top).size();
    for(int i = 1; i < col; i++){

            QWidget* w = cells->at(top)[i];
            QPushButton* p = dynamic_cast<QPushButton*>(w);

            if(mode.compare("overview") == 0){
                connect(p, SIGNAL(clicked(bool)), this, SLOT(open_project_reading_mode()));
            }else if(mode.compare("read") == 0){
                p->setEnabled(false);
                //connect(p, SIGNAL(clicked(bool)), this, SLOT(open_project_writing_mode()));
            }else if(mode.compare("write") == 0){
                if(i == 1){
                    connect(p, SIGNAL(clicked(bool)), this, SLOT(edit_existing_project()));
                }else{
                    connect(p, SIGNAL(clicked(bool)), this, SLOT(open_process_edit_dialog()));
                }
            }
     }

}

QString MainWindow::get_element_title_from_push_button(QPushButton* pb, std::vector<Project>* items){

    int i;
    int s = cells->size();
    for(int i = 0; i < cells->at(s-1).size()-1; i++){
        if(i > 0){
            QString id = items->at(i).get_title();
            QPushButton* p = dynamic_cast<QPushButton*>(cells->at(s-1)[i]);
            if(p == pb){
                return items->at(i).get_title();
            }
        }
        i++;
    }
    return NULL;
}

QString MainWindow::get_element_title_from_push_button(QPushButton* pb, std::vector<Process>* items){

    int i;
    for(QWidget* w : cells->at(cells->size()-1)){
        if(i > 0){
            QPushButton* p = dynamic_cast<QPushButton*>(w);
            if(p == pb){
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
   _main->ui->pb_store->setEnabled(true);
   _main->ui->pb_reload->setEnabled(true);
   _main->ui->pb_to_store->setVisible(false);
   _main->ui->pb_to_store->setEnabled(false);
   _main->ui->pb_new->setEnabled(true);
   _main->ui->pb_source->setEnabled(true);
   _main->ui->pb_back->setEnabled(false);
   _main->ui->pb_annotation->setEnabled(false);
   _main->ui->lbl_title->setText(" ");
   open_overview();
}

bool MainWindow::OverviewState::open_overview(){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    for(int i = 0; i < _main->projects->size(); i++){
        _main->ms_box.add_date_based_item(&(_main->projects->at(i)));
    }
    _main->ms_box.build_layout();
    _main->content_l = _main->ms_box.get_layout_container();
    _main->update();
    _main->barLayout->addLayout(_main->content_l);
    _main->update();
    _main->connect_project_cells("overview");

    return true;
}

bool MainWindow::OverviewState::open_project_read(QString id){

    _main->clear_layout(_main->barLayout);
    _main->ms_box.clear_all();
    _main->state = new ProjectReadState(_main);

    return true;
}

bool MainWindow::OverviewState::create_new_element(){

    _main->trans_project = new Project();
    CreateProjectDialog* cpd = new CreateProjectDialog(_main->trans_project);
    cpd->show();
    connect(cpd, SIGNAL(accepted()), _main, SLOT(handle_new_project()));

    return true;
}

bool MainWindow::OverviewState::reload(){
    _main->ms_box.clear_all();
    _main->state->open_overview();
    return true;
}

MainWindow::ProjectReadState::ProjectReadState(MainWindow* main) : WindowState(main){

    _main->ui->pb_edit->setEnabled(true);
    _main->ui->pb_reload->setEnabled(true);
    _main->ui->pb_source->setEnabled(false);
    _main->ui->pb_new->setEnabled(false);
    _main->ui->pb_back->setEnabled(true);
    _main->ui->pb_to_store->setVisible(false);
    _main->ui->pb_to_store->setEnabled(false);
    _main->ui->pb_store->setEnabled(false);
    _main->ui->pb_annotation->setEnabled(true);

    _main->ui->pb_edit->setText("bearbeiten");
    _main->ui->lbl_title->setText(_main->trans_project->get_id());
    disconnect(_main->ui->pb_edit, SIGNAL(clicked(bool)), _main, SLOT(close_project_writing_mode()));
    connect(_main->ui->pb_edit, SIGNAL(clicked(bool)), _main, SLOT(open_project_writing_mode()));

    open_project_read(_main->trans_project->get_id());
}

bool MainWindow::ProjectReadState::open_project_read(QString id){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    /*
    Project* p = _main->project_manager.get_project_by_id(id);
    _main->trans_project = p;
    */

        _main->ms_box.add_date_based_item(_main->trans_project);
    for(Process* pc : _main->trans_project->get_processes()){
        _main->ms_box.add_date_based_item(pc);
    }

    _main->ms_box.build_layout("_f_over");
    _main->barLayout->addLayout(_main->ms_box.get_layout_container());
    _main->connect_project_cells("read");

    return true;
}

bool MainWindow::ProjectReadState::open_overview(){

    _main->clear_layout(_main->barLayout);
    _main->ms_box.clear_all();
    _main->state = new OverviewState(_main);

    return true;
}

bool MainWindow::ProjectReadState::open_project_write(QString id){

    if(!_main->project_manager.get_project_by_id(id)->is_writable()){
        return false;
    }
    _main->project_manager.open_edit_mode(id);

    _main->clear_layout(_main->barLayout);
    _main->ms_box.clear_all();
    _main->state = new ProjectWriteState(_main);

    return true;
}

bool MainWindow::ProjectReadState::reload(){
    _main->ms_box.clear_all();
    _main->state->open_project_read(_main->trans_project->get_id());
    return true;
}

MainWindow::ProjectWriteState::ProjectWriteState(MainWindow* main) : WindowState(main){

    _main->ui->pb_new->setEnabled(true);
    _main->ui->pb_reload->setEnabled(false);
    _main->ui->pb_source->setEnabled(false);
    _main->ui->pb_edit->setEnabled(true);
    _main->ui->pb_store->setEnabled(false);
    _main->ui->pb_to_store->setVisible(true);
    _main->ui->pb_to_store->setEnabled(true);
    _main->ui->pb_back->setEnabled(false);
    _main->ui->pb_annotation->setEnabled(true);

    _main->ui->pb_edit->setText("speichern");

    disconnect(_main->ui->pb_edit, SIGNAL(clicked(bool)), _main, SLOT(open_project_writing_mode()));
    connect(_main->ui->pb_edit, SIGNAL(clicked(bool)), _main, SLOT(close_project_writing_mode()));

    open_project_write(_main->trans_project->get_id());
}

bool MainWindow::ProjectWriteState::open_project_read(QString id){

    _main->clear_layout(_main->barLayout);
    _main->ms_box.clear_all();
    _main->state = new ProjectReadState(_main);

    return true;
}

bool MainWindow::ProjectWriteState::open_project_write(QString id){

    _main->project_manager.load_active_projects();
    _main->projects = _main->project_manager.get_open_projects();

    Project* p = _main->project_manager.get_project_by_id(id);

    _main->ms_box.add_date_based_item(_main->trans_project);
    for(Process* pc : p->get_processes()){
       _main->ms_box.add_date_based_item(pc);
    }

    _main->ms_box.build_layout("_f_over");
    _main->barLayout->addLayout(_main->ms_box.get_layout_container());
    _main->connect_project_cells("write");

    return true;
}

bool MainWindow::ProjectWriteState::create_new_element(){

    _main->trans_process = new Process();
    ProcessDialog* pd = new ProcessDialog(_main->trans_process, _main->user_index.to_string_list());
    pd->show();
    connect(pd, SIGNAL(accepted()), _main, SLOT(handle_new_process()));

    return true;
}

bool MainWindow::ProjectWriteState::reload(){
    _main->ms_box.clear_all();
    _main->state->open_project_write(_main->trans_project->get_id());
    return true;
}
