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

QString Project::get_id(){
    return ID;
}

QString Project::get_title(){
    return get_id();
}

bool Project::is_writable(){
    return is_writable();
}

void Project::set_writeable(bool w){
    WRITEABLE = w;
}

std::vector<Process>* Project::get_processes(){

    std::vector<Process*> procs;

    for(Process p : processes){
        procs.push_back(&p);
    }

    return procs;
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

    if(state_hint.compare("stock") == 0){
        state = StockedState();
    }else{
        if(is_finished()){
            state = FinishedState();
        }else if(is_late()){
            state = LateState();
        }else if(is_nearly_late()){
            state = NearlyLateState();
        }else{
            state = OpenState();
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
    state.set_finished();
}

bool Project::move_to_stock(){
    state.set_stocked();
}

bool Project::set_nearly_late(){
    state.set_nearly_late();
}

bool Project::set_late(){
    state.set_late();
}

bool Project::set_open(){
    state.set_open();
}

QString Project::get_state(){
    return state.to_string();
}
