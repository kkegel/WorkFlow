#include "../../header/projectfilereader.h"

ProjectFileReader::ProjectFileReader()
{

}

bool ProjectFileReader::check_file_existence(QString path){

    return SystemFileReader::check_file_existence(path);
}

QString ProjectFileReader::get_file(QString path){

    return SystemFileReader::get_file(path);
}
