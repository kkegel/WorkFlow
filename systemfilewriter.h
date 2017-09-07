#ifndef SYSTEMFILEWRITER_H
#define SYSTEMFILEWRITER_H

#include <QString>
#include <QFile>
#include <QTextStream>

class SystemFileWriter
{
public:

    SystemFileWriter();

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

#endif // SYSTEMFILEWRITER_H
