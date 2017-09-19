#include "systemfilewriter.h"

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
