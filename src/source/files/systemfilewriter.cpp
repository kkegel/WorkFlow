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

#include "../../header/systemfilewriter.h"

SystemFileWriter::SystemFileWriter()
{

}

bool SystemFileWriter:: set_to_file(QString path, QString content){

    QFile file(path);

        if(!file.open(QFile::WriteOnly |
                      QFile::Text))
        {
            //qDebug() << "error opening file";
            return false;
        }

        QTextStream out(&file);
        out << content;
        file.flush();
        file.close();

        return true;
}
