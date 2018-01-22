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

#ifndef USERINDEX_H
#define USERINDEX_H

#include <QString>
#include <QStringList>

#include <vector>

#include "datahandler.h"
#include "filedatahandler.h"

class UserIndex
{
public:

    UserIndex(){}

    UserIndex(DataHandler* dh) {
        this->dh = dh;
        load_user();
    }

    void add_user(QString name){
        if(!contains_user(name) && name.compare("") != 0){
            user.push_back(name);
            dh->set_user(user);
            load_user();
        }
    }

    void remove_user(QString name){
        for(int i = 0; i < user.size(); i++){
            if(user[i].compare(name) == 0){
                user.erase(user.begin()+i, user.begin()+i+1);
                dh->set_user(user);
                load_user();
            }
        }
    }

    void remove_user(){
        user.clear();
        dh->set_user(user);
        load_user();
    }

    std::vector<QString> get_all_user(){
        load_user();
        return user;
    }

    QString get_all_user_string(){
        load_user();
        QString s = "";
        for(QString u : user){
            s += u + ", ";
        }
        return s;
    }

    void load_user(){
        user = dh->get_user();
    }

    bool contains_user(QString name){
        for(QString n : user){
            if(n.compare(name) == 0){
                return true;
            }
        }
        return false;
    }

    QStringList to_string_list(){
        QStringList list;
        for(QString s : user){
            list.append(s);
        }
        return list;
    }

private:

    DataHandler* dh;
    std::vector<QString> user;
};

#endif // USERINDEX_H
