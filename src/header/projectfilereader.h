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

#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include <QString>
#include <QFile>

#include "systemfilereader.h"

class ProjectFileReader
{
public:

    ProjectFileReader();

    /**
     * @brief check_file_existence
     * @param path
     * @return bool
     *
     * checks if the file at the given position is existing
     *
     */

    static bool check_file_existence(QString path);

    /**
     * @brief get_file
     * @param path
     * @return QString
     *
     * reads the file at the given position and
     * returns its text content as QString
     *
     */

    static QString get_file(QString path);

};

#endif // PROJECTFILEREADER_H
