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
        if(!contains_user(name)){
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
