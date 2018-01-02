#ifndef PROJECTFILEWRITER_H
#define PROJECTFILEWRITER_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include "systemfilewriter.h"

class ProjectFileWriter
{
public:

    ProjectFileWriter();

    /**
     * @brief set_to_file
     * @param path
     * @param content
     * @return
     *
     * writes content to file without manipulating ist.
     * true, if succesfull, else false (mabe no write permissions or path not valid)
     *
     */

    static bool set_to_file(QString path, QString content);

};

#endif // PROJECTFILEWRITER_H
