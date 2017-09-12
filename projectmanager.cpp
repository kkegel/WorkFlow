#include "projectmanager.h"

ProjectManager::ProjectManager()
{
    data_handler = new FileDataHandler("/home/kkegel/Documents/");
    load_active_projects();
}

void ProjectManager::load_active_projects(){

    for(QString id : data_handler->get_open_project_ids()){
        projects.push_back(data_handler->get_project_by_id(id));
    }

}

bool ProjectManager::open_edit_mode(QString project_id){

    reload_project(project_id);
    Project *p = get_project_by_id(project_id);

    if(! p->is_writable()){
        return false;
    }

    p->set_writeable(false);

    return data_handler->set_project(*p);
}

bool ProjectManager::close_edit_mode(QString project_id){

    Project *p = get_project_by_id(project_id);
    p->set_writeable(true);

    return data_handler->set_project(*p);
}

void ProjectManager::save_project(Project* p){
    data_handler->set_project(*p);
}

std::vector<Project>* ProjectManager::get_open_projects(){

    return &projects;
}

void ProjectManager::reload_project(QString project_id){

    Project p = data_handler->get_project_by_id(project_id);
    projects[get_project_index_by_id(project_id)] = p;

}

void ProjectManager::reload_all_projects(){

    for(Project p : projects){
        reload_project(p.get_id());
    }
}

Project* ProjectManager::get_project_by_id(QString project_id){

    return &(projects[get_project_index_by_id(project_id)]);
}

int ProjectManager::get_project_index_by_id(QString project_id){

    for(int i = 0; i < projects.size(); i++){
        if(project_id.compare(projects[i].get_id()) == 0){
            return i;
        }
    }

    return -1;
}

void ProjectManager::set_source(QString source){
    data_handler->set_source(source);
}
