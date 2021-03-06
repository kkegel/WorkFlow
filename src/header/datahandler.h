/**
  This file is part of WorkFlow.

  WorkFlow is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  WorkFlow is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

  Copyright (C) Karl Kegel (github: kkegel) 2018
*/

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

    virtual std::vector<QString> get_open_project_ids() = 0;

    virtual std::vector<QString> get_stored_project_ids() = 0;

    /**
     * @brief get_all_project_ids
     * @return
     *
     * gets all project id's within the current workspace
     */

    virtual std::vector<QString> get_all_project_ids() = 0;

    /**
     * @brief get_project_by_id
     * @param id
     * @return
     *
     * builds a Project class from the data provided by the data backend
     * with the id as data key
     */

    virtual Project get_project_by_id(QString id) = 0;

    /**
     * @brief set_project
     * @param id
     * @param p
     * @return
     *
     * saves the Project in the data backend (persistent)
     */

    virtual bool set_project(Project p) = 0;

    virtual bool delete_project(QString id) = 0;

    QString get_type();

    virtual void set_source(QString source) = 0;

    virtual void set_user(std::vector<QString> users) = 0;
    virtual std::vector<QString> get_user() = 0;

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
