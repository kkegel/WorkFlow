#include "commander.h"

QStringList Commander::execute_command(QString command){

    QStringList parts = split_command(command);
    QString head = parts[0];
    QString tail = parts[1];

    if(head.compare("nutzer-hinzufügen") == 0){
        parts.append("0");
    }else if(head.compare("nutzer-löschen") == 0){
        if(tail.compare("alle") == 0){
            parts.append("10");
        }else{
            parts.append("11");
        }
    }else if(head.compare("nutzer-anzeigen") == 0){
        if(tail.compare("alle") == 0){
            parts.append("20");
        }else{
            parts.append("21");
        }
    }else if(head.compare("anzeigen") == 0){
        if(tail.compare("heute") == 0){
            parts.append("30");
        }
    }else{
        parts.append("-1");
    }

    return parts;
}

QStringList Commander::split_command(QString command){

    QStringList parts = command.split(' ');

    if(parts.size() < 2){
        parts.append(" ");
        parts.append(" ");
        return parts;
    }

    QString head = parts[0];
    QString tail = parts[1];

    for(int i = 2; i < parts.size(); i++){
        tail += parts[i];
    }

    QStringList c_l({head, tail});
    return c_l;
}


