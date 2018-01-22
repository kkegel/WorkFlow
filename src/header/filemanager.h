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

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QStandardPaths>
#include <QDir>

#include "projectfilereader.h"
#include "projectfilewriter.h"

#include <stdio.h>
#include <iostream>

class FileManager
{
public:

    /**
     * @brief FileManager
     * @param path_root
     *
     * Constructor. path_root defines the path to the root direcotry
     * of the index.xml file
     */

    FileManager(QString path_root);
    FileManager(){}


    /**
     * @brief check_file_existence
     * @param path
     * @return bool
     *
     * checks if the file at the given position is existing
     *
     */

    bool check_existence(QString id);

    /**
     * @brief get_file
     * @param path
     * @return QString
     *
     * reads the file at the given position and
     * returns its text content as QString
     *
     */

    QString get_file(QString id);

    /**
     * @brief set_to_file
     * @param path
     * @param content
     * @return
     *
     * writes content to file without manipulating ist.
     * true, if succesfull, else false (mabe no write permissions or path not valid)
     *
     */

    bool set_to_file(QString id, QString content);

    void set_source(QString source);

private:

    /**
     * @brief PATH_ROOT
     *
     * the directory root to the directory with the index.xml file and
     * the other project.xml files
     *
     * is set in Constructor
     */

    QString PATH_ROOT = "";

    QString get_source();

};

#endif // FILEMANAGER_H
