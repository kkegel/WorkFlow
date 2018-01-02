#include "../../header/filemanager.h"
// #include <QErrorMessage>

FileManager::FileManager(QString path_root)
{
    QString s = get_source();

    if(s.size() > 9){
        this->PATH_ROOT = s.left(s.size()-9);//path_root;
    }else{
        this->PATH_ROOT = s;
    }

   // QErrorMessage* err = new QErrorMessage();
   // err->showMessage(PATH_ROOT);

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
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    if (!QDir(path).exists()) {
            if (!QDir().mkdir(path)) {
                std::cout << "no permissions to build file!" << std::endl;
            }
        }
    path += "/stats.txt";
    std::cout << path.toStdString() << std::endl;
    ProjectFileWriter::set_to_file(path, source);
    PATH_ROOT = source;
}

QString FileManager::get_source(){
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    path += "/stats.txt";
    std::cout << path.toStdString() << std::endl;
    return ProjectFileReader::get_file(path);
}
