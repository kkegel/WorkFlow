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

#ifndef FILEDATAHANDLER_H
#define FILEDATAHANDLER_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDate>

#include <vector>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <thread>
#include <chrono>

#include "project.h"
#include "filemanager.h"
#include "datahandler.h"

/**
 * @brief The FileDataHandler class
 *
 * a concrete implementation of the DataHandler class
 * implements the xml-file variant of the data backend
 */

class FileDataHandler : public DataHandler
{
public:

    /**
     * @brief FileDataHandler
     * @param DATA_ROOT
     *
     * Constructor. DATA_ROOT is the path, where the
     * used worksapce directory is situated
     */

    FileDataHandler(QString DATA_ROOT);
    FileDataHandler(){}

    /**
     * @brief get_all_project_ids
     * @return
     *
     * gets all project id's within the current workspace
     *
     * overrides function from DataHandler
     */

    std::vector<QString> get_all_project_ids() override;

    /**
     * @brief get_open_project_ids
     * @return
     *
     * gets all the ids from projects with the state "open"
     *
     * overrides function from DataHandler
     */

    Project get_project_by_id(QString id) override;

    /**
     * @brief set_project
     * @param id
     * @param p
     * @return
     *
     * saves the Project in the data backend (persistent)
     *
     * overrides function from DataHandler
     */

    std::vector<QString> get_open_project_ids() override;

    std::vector<QString> get_stored_project_ids() override;

    /**
     * @brief get_project_by_id
     * @param id
     * @return
     *
     * builds a Project class from the data provided by the data backend
     * with the id as data key
     *
     * overrides function from DataHandler
     */

    bool set_project(Project p) override;

    bool delete_project(QString id) override;

    void set_source(QString source) override;

    void set_user(std::vector<QString> users) override;
    std::vector<QString> get_user() override;

private:

    /**
     * @brief build_project_from_data
     * @param data
     * @return
     *
     * takes the raw string data from a file and creates
     * a project class containing that data
     */

    Project build_project_from_data(QString data);

    /**
     * @brief build_data_from_project
     * @param p
     * @return
     *
     * creates a xml file format string used for the FileData backend
     */

    QString build_data_from_project(Project p);

    /**
     * @brief get_xml_value_from_data
     * @param data
     * @param opening
     * @return
     *
     * searches for the first existence of the opening xml-tag an
     * returns the content between this opening and its coorresponding closening tag
     */

    QString get_xml_value_from_data(QString data, QString opening, int number = 0);

    /**
     * @brief get_number_processes_from_data
     * @param data
     * @return
     *
     * counts how many elements are defined in one project data xml-string
     */

    int get_number_elements_from_data(QString data, QString element);

    /**
     * @brief get_process_from_data
     * @param data
     * @param number_process
     * @return
     *
     * creates a new Process object from the process data
     * at the given position in the project-xml-string (first is 1)
     */

    Process get_process_from_data(QString data, int number_process);

    /**
     * @brief get_process_data_from_project
     * @param p
     * @return
     *
     * builds a xml-string from the process data provided by the given
     * project. the string has to be used writing the project data to project-xml file
     */

    QString get_process_data_from_project(Project p);

    /**
     * @brief add_to_index
     * @param id
     * @return
     *
     * adds the give id to the index.xml file
     */

    bool add_to_index(QString id);

    /**
     * @brief file_manager
     *
     * the specific FileManager createt in the Constructure with its
     * specific arguments
     */

    FileManager file_manager;

};

#endif // FILEDATAHANDLER_H
