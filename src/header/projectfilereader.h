#ifndef PROJECTFILEREADER_H
#define PROJECTFILEREADER_H

#include <QString>
#include <QFile>

#include "systemfilereader.h"

class ProjectFileReader
{
public:

    ProjectFileReader();

    /**
     * @brief check_file_existence
     * @param path
     * @return bool
     *
     * checks if the file at the given position is existing
     *
     */

    static bool check_file_existence(QString path);

    /**
     * @brief get_file
     * @param path
     * @return QString
     *
     * reads the file at the given position and
     * returns its text content as QString
     *
     */

    static QString get_file(QString path);

};

#endif // PROJECTFILEREADER_H
