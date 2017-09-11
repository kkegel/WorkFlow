#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDate>
#include <QDateTime>

#include <vector>

#include "projectitem.h"
#include "process.h"
#include "projectstate.h"

/**
 * @brief The Project class
 *
 * the representation of a project.
 * the Project class is the core class of ProjectManagment
 * it saves all classifing information about a project.
 */

class Project : public ProjectItem
{
public:

    /*
     * for information about parameters, look at the variable and method comments
     */

    Project(QDate start_time, QDate end_time, QString ID, bool WRITEABLE,
            std::vector<Process> processes, QString state_hint);
    Project(){}

    /**
     * @brief get_id
     * @return
     *
     * the unifing id key of a project
     */

    QString get_id();

    /**
     * @brief is_writable
     * @return
     *
     * true, if project file is not in writing mode
     * false, if project file is opened in writing mode (other user or oneself)
     */

    bool is_writable();

    /*
     * only called by methods knowing what they are doing.
     * IMPORTANT: if it becomes changed, there must be changed the corresponding file
     * as well or the programm will produce random unlocatable mistakes.
     */

    void set_writeable(bool w);

    std::vector<Process*> get_processes();
    std::vector<Process>* get_processes_p();

    Process* get_process_by_name(QString name);

    /**
     * @brief delete_process
     * @param name
     *
     * delets a process by its unifing name.
     * change is not saved automatically
     */

    void delete_process(QString name);

    /**
     * @brief add_process
     * @param p
     *
     * adds a process to the intern procces vector
     * no check if process is valid
     * change is not saved automatically
     */

    void add_process(Process p);

    /*
     * state maschine manipulation methods.
     * look at projectstate.h for more information
     */

    bool set_finished();
    bool move_to_stock();
    bool set_nearly_late();
    bool set_late();
    bool set_open();

    /**
     * @brief get_state
     * @return
     *
     * returns a charakteristic string for each state
     * look at projectstate.h for more information
     */

    QString get_state();

    QString get_title();

private:

    QString ID;
    bool WRITEABLE;
    std::vector<Process> processes;

    /**
     * @brief state
     *
     * the current state of the project.
     * look at projectstate.h for more information
     */

    ProjectState state;

    /**
     * @brief determine_state
     * @param state_hint
     *
     * uses the state hint given by the data backend or state switching actions,
     * to figure out, which state the project has, if its not easily done by stateswitching.
     */

    void determine_state(QString state_hint);

    /*
     * some helpful methods working on the projectstate
     */

    bool is_finished();
    bool is_late();
    bool is_nearly_late();

};

#endif // PROJECT_H
