#include "systemfilereader.h"

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
