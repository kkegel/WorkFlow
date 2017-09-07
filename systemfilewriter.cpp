#include "systemfilewriter.h"

SystemFileWriter::SystemFileWriter()
{

}

bool SystemFileWriter:: set_to_file(QString path, QString content){

    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) {

        file.close();
        return false;
    }

    QTextStream out(&file);
    out << content;

    file.close();
    return true;
}
