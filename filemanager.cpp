#include "filemanager.h"

FileManager::FileManager(QString path_root)
{
    this->PATH_ROOT = get_source();//path_root;
}

bool FileManager::check_existence(QString id){

    return ProjectFileReader::check_file_existence(PATH_ROOT+id+".xml");
}

QString FileManager::get_file(QString id){

    return ProjectFileReader::get_file(PATH_ROOT+id+".xml");
}

bool FileManager::set_to_file(QString id, QString content){

    return ProjectFileWriter::set_to_file(PATH_ROOT+id+".xml", content);
}

void FileManager::set_source(QString source){
    ProjectFileWriter::set_to_file(QDir::currentPath()+"stats.txt", source);
    PATH_ROOT = source;
}

QString FileManager::get_source(){
    return ProjectFileReader::get_file(QDir::currentPath()+"stats.txt");
}
