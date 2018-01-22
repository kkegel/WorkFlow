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

#include "../../header/systemfilereader.h"

SystemFileReader::SystemFileReader()
{

}

bool SystemFileReader::check_file_existence(QString path){

    QFile file(path);
    if(!file.open(QFile::ReadOnly |
                      QFile::Text))
        {
            //qDebug() << "could not open file";
            return false;
        }

    file.close();
    return true;
}

QString SystemFileReader::get_file(QString path){

    QFile file(path);

    if(!file.open(QFile::ReadOnly |
                      QFile::Text))
        {
            //qDebug() << "could not open file";
            return "";
        }

    QTextStream in(&file);
    QString text = in.readAll();

    file.close();

    return text;
}
