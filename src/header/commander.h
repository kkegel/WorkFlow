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

#ifndef COMMANDER_H
#define COMMANDER_H

#include <QString>
#include <QStringList>
#include <QErrorMessage>

#include <vector>

/*
 * commands:
 *
 * nutzer-hinzufügen Name
 * nutzer-löschen Name
 * nutzer-anzeigen alle
 * nutzer-anzeigen Name
 */

class Commander
{
public:

    Commander(){}

    QStringList execute_command(QString command);

private:

    QStringList split_command(QString command);

};

#endif // COMMANDER_H
