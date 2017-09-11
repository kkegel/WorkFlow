#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QDir>

#include "projectfilereader.h"
#include "projectfilewriter.h"

class FileManager
{
public:

    /**
     * @brief FileManager
     * @param path_root
     *
     * Constructor. path_root defines the path to the root direcotry
     * of the index.xml file
     */

    FileManager(QString path_root);
    FileManager(){}


    /**
     * @brief check_file_existence
     * @param path
     * @return bool
     *
     * checks if the file at the given position is existing
     *
     */

    bool check_existence(QString id);

    /**
     * @brief get_file
     * @param path
     * @return QString
     *
     * reads the file at the given position and
     * returns its text content as QString
     *
     */

    QString get_file(QString id);

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

    bool set_to_file(QString id, QString content);

    void set_source(QString source);

private:

    /**
     * @brief PATH_ROOT
     *
     * the directory root to the directory with the index.xml file and
     * the other project.xml files
     *
     * is set in Constructor
     */

    QString PATH_ROOT = "";

    QString get_source();

};

#endif // FILEMANAGER_H
