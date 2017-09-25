#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QString>

#include <vector>

#include "project.h"
#include "process_.h"
#include "datahandler.h"
#include "filedatahandler.h"
#include "projectitem.h"
#include "project.h"

class ProjectManager
{
public:

    ProjectManager();

    void load_active_projects();
    bool open_edit_mode(QString project_id);
    std::vector<Project>* get_open_projects();
    bool close_edit_mode(QString project_id);
    void reload_project(QString project_id);
    void reload_all_projects();
    void save_project(Project* p);
    Project* get_project_by_id(QString project_id);

    void set_source(QString source);
    DataHandler* get_data_handler();

private:

    DataHandler* data_handler;
    std::vector<Project> projects;

    int get_project_index_by_id(QString project_id);

};

#endif // PROJECTMANAGER_H
