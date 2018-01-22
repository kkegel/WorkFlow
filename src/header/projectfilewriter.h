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

#ifndef PROJECTFILEWRITER_H
#define PROJECTFILEWRITER_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include "systemfilewriter.h"

class ProjectFileWriter
{
public:

    ProjectFileWriter();

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

    static bool set_to_file(QString path, QString content);

};

#endif // PROJECTFILEWRITER_H
