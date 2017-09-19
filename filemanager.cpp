#include "filemanager.h"

FileManager::FileManager(QString path_root)
{
    QString s = get_source();

    if(s.size() > 9){
        this->PATH_ROOT = s.left(s.size()-9);//path_root;
    }else{
        this->PATH_ROOT = s;
    }

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
    QString path = QDir::currentPath()+"/stats.txt";
    ProjectFileWriter::set_to_file(path, source);
    PATH_ROOT = source;
}

QString FileManager::get_source(){
    QString path = QDir::currentPath()+"/stats.txt";
    return ProjectFileReader::get_file(path);
}
