#include "systemfilereader.h"

SystemFileReader::SystemFileReader()
{

}

bool SystemFileReader::check_file_existence(QString path){

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {

        file.close();
        return false;
    }
    file.close();
    return true;
}

QString SystemFileReader::get_file(QString path){

     QFile file(path);
     QString text = "";

     QTextStream in(&file);

     while(!in.atEnd()) {

         QString line = in.readLine();
         text += line;
     }
     file.close();
     return text;
}
