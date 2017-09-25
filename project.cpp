#include "project.h"

Project::Project(QDate start_time, QDate end_time, QString ID, bool WRITEABLE,
                 std::vector<Process> processes, QString state_hint) :
    ProjectItem(start_time, end_time)
{
    this->ID = ID;
    this->WRITEABLE = WRITEABLE;
    this->processes = processes;

    determine_state(state_hint);
}

Project::Project() : ProjectItem(QDate::currentDate(), QDate::currentDate()){

    ID = "";
    WRITEABLE = false;
    determine_state("open");
}

QString Project::get_id(){
    return ID;
}

QString Project::get_title(){
    return get_id();
}

bool Project::is_writable(){
    return WRITEABLE;
}

void Project::set_writeable(bool w){
    WRITEABLE = w;
}

QString Project::get_state_hint(){

    if(get_state().compare("STOCKED_STATE") == 0){
        return "stock";
    }else{
        return "open";
    }
}

std::vector<Process*> Project::get_processes(){

    std::vector<Process*> procs;

    for(int i = 0; i < processes.size(); i++){
        procs.push_back(&(processes[i]));
    }

    return procs;
}

std::vector<Process>* Project::get_processes_p(){
    return &processes;
}

Process* Project::get_process_by_name(QString name){

    for(Process *p : get_processes()){
        if(p->get_name().compare(name) == 0){
            return p;
        }
    }

    return nullptr;
}

void Project::delete_process(QString name){

    for(int i = 0; i < processes.size(); i++){
        if(processes[i].get_name().compare(name)){
            processes.erase(processes.begin()+i);
            break;
        }
    }
    determine_state("open");
}

void Project::add_process(Process p){
    processes.push_back(p);
    determine_state("open");
}

void Project::determine_state(QString state_hint){

    ProjectState* p = new OpenState();

    if(state_hint.compare("stock") == 0){
        state = new StockedState();
    }else{
        if(is_finished()){
            state = new FinishedState();
        }else if(is_late()){
            state = new LateState;
        }else if(is_nearly_late()){
            state = new NearlyLateState();
        }else{
           state = new OpenState();
        }
    }
}

bool Project::is_finished(){

    for(Process p : processes){
        if(p.get_state().compare("COMPLETED_STATE") != 0){
            return false;
        }
    }
    return true;
}

bool Project::is_late(){

    for(Process p : processes){
        if(p.get_state().compare("LATE_STATE") == 0){
            return true;
        }
    }
    return false;
}

bool Project::is_nearly_late(){

    if(is_finished() || is_late()){
        return false;
    }

    for(Process p : processes){
        if(p.get_state().compare("NEARLY_LATE_STATE") == 0){
            return true;
        }
    }
    return false;
}

bool Project::set_finished(){
    state = state->set_finished();
    return true;
}

bool Project::move_to_stock(){
    state = state->set_stocked();
    return true;
}

bool Project::set_nearly_late(){
    state = state->set_nearly_late();
    return true;
}

bool Project::set_late(){
    state = state->set_late();
    return true;
}

bool Project::set_open(){
    state = state->set_open();
    return true;
}

QString Project::get_state(){
    if(state != NULL){
        return state->to_string();
    }
    return "";
}
