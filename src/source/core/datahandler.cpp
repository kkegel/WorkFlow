#include "../../header/datahandler.h"

DataHandler::DataHandler(QString TYPE)
{
    this->TYPE = TYPE;
}

QString DataHandler::get_type(){

    return TYPE;
}
