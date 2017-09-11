#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QString>

#include <vector>

#include "project.h"

/**
 * @brief The DataHandler class
 *
 * this class is part of a pettern for easy extensionability.
 * the ProjectManager class uses this virtual class methods to do its stuff.
 * so it is independent from the current implementation of the data backend
 * but konws from the TYPE, which backend is used (error handling i.e.)
 */

class DataHandler
{
public:

    /**
     * @brief DataHandler
     * @param TYPE
     *
     * Constructor. TYPE defines the type of data backend which
     * is used by its child class
     */

    DataHandler(QString TYPE);
    DataHandler(){}

    /**
     * @brief get_open_project_ids
     * @return
     *
     * gets all the ids from projects with the state "open"
     */

    std::vector<QString> get_open_project_ids();

    /**
     * @brief get_all_project_ids
     * @return
     *
     * gets all project id's within the current workspace
     */

    std::vector<QString> get_all_project_ids();

    /**
     * @brief get_project_by_id
     * @param id
     * @return
     *
     * builds a Project class from the data provided by the data backend
     * with the id as data key
     */

    Project get_project_by_id(QString id);

    /**
     * @brief set_project
     * @param id
     * @param p
     * @return
     *
     * saves the Project in the data backend (persistent)
     */

    bool set_project(Project p);

    QString get_type();

    void set_source(QString source);

private:

    /**
     * @brief TYPE
     *
     * contains the information, which kind of datahandler is used
     * like "FILE_XML_TYPE" or "DATABASE_SQL_TYPE" and so on
     */

    QString TYPE;

};

#endif // DATAHANDLER_H
