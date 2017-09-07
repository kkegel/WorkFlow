#include "projectfilewriter.h"

ProjectFileWriter::ProjectFileWriter()
{

}

bool ProjectFileWriter:: set_to_file(QString path, QString content){

    return SystemFileWriter::set_to_file(path, content);
}
