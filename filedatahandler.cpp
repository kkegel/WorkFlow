#include "filedatahandler.h"

FileDataHandler::FileDataHandler(QString DATA_ROOT) : DataHandler("FILE_XML_TYPE")
{
    this->file_manager = FileManager(DATA_ROOT);
}

std::vector<QString> FileDataHandler::get_all_project_ids(){

    QString project_index = file_manager.get_file("index");

    project_index.remove('\r'); //remove returns
    QStringList lines = project_index.split('\n');

    std::vector<QString> ids;

    bool xml_open = false;
    QString last = " ";
    for(QString line : lines){
        if(!xml_open){
            if(line.compare("<index>") == 0){
                xml_open = true;
            }else if(line.compare("</index>") == 0){
                break;
            }
        }else{
            if(last.compare("<project-source>") == 0){
                ids.push_back(line);
            }
        }
        last = line;
    }

    return ids;
}

Project FileDataHandler::get_project_by_id(QString id){
    return build_project_from_data(file_manager.get_file(id));
}

std::vector<QString> FileDataHandler::get_open_project_ids(){

    std::vector<QString> open_ids;

    std::vector<QString> ids = get_all_project_ids();
    for(QString id : ids){
        if(get_xml_value_from_data(file_manager.get_file(id), "<state>").compare("open") == 0){
            open_ids.push_back(id);
        }
    }

    return open_ids;
}

bool FileDataHandler::set_project(Project p){

    bool is_available = false;

    for(QString id : get_all_project_ids()){
         if(id.compare(p.get_id()) == 0){
             is_available = true;
             break;
         }
    }

    if(!is_available){
        add_to_index(p.get_id());
    }

    return file_manager.set_to_file(p.get_id(), build_data_from_project(p));
}

Project FileDataHandler::build_project_from_data(QString data){

    int number_processes = get_number_processes_from_data(data);
    std::vector<Process> processes;

    for(int i = 1; i <= number_processes; i++){
        processes.push_back(get_process_from_data(data, i));
    }

    bool writeable = false;
    if(get_xml_value_from_data(data, "<writeable").toInt() == 1){
        writeable = true;
    }

    return Project(QDate::fromString(get_xml_value_from_data(data, "<start-date>")),
                       QDate::fromString(get_xml_value_from_data(data, "<end-date>")),
                       get_xml_value_from_data(data, "<id>"),
                       writeable,
                       processes,
                       get_xml_value_from_data(data, "<state>"));

}

QString FileDataHandler::build_data_from_project(Project p){

    QString writable;
    if(p.is_writable()){
        writable = "1";
    }else{
        writable = "0";
    }

    QString state_hint;
    if(p.get_state().compare("STOCKED_STATE") == 0){
        state_hint = "stock";
    }else{
        state_hint = "open";
    }

    QString data = QString("<project>\n")
              +  "<data>\n"
                 +  "<writeable>\n"
                    + writable;
                 +  "</writeable>\n"
                 +  QString("<id>\n")
                    + p.get_id() + "\n"
                 +  "</id>\n"
                 +  "<state>\n"
                    + state_hint + "\n"
                 +  "</state>\n"
                 +  "<time>\n"
                     +  "<start-time>\n"
                        + p.get_start_time().toString() + "\n"
                     +  "</start-time\n"
                     +  "<end-time>\n"
                        + p.get_end_time().toString() + "\n"
                     +  "</end-time>\n"
                 +  "</time>\n"
                 +  "<content>\n"
                    + get_process_data_from_project(p)
                 +  "</content>\n"
             +  "</data>\n"
         +  "</project>";

    return data;
}

QString FileDataHandler::get_xml_value_from_data(QString data, QString opening){

    data.remove('\r'); //remove returns
    QStringList lines = data.split('\n');

    QString last = "";
    QString searched = "";

    bool opened = false;

    for(QString line : lines){
        if(line.compare(opening) == 0){
            opened = true;
        }else if(line.compare("</"+opening.mid(1,opening.size()-2)) == 0){
            break;
        }else{
            if(last.compare(opening) == 0){
                searched += line;
            }else{
                searched += "\n" + line;
            }
        }
        last = line;
    }

    return searched;
}

int FileDataHandler::get_number_processes_from_data(QString data){

    data.remove('\r'); //remove returns
    QStringList lines = data.split('\n');

    int number_processes = 0;

    for(QString line : lines){
        if(line.compare("<process>") == 0){
            number_processes++;
        }
    }

    return number_processes;
}

Process FileDataHandler::get_process_from_data(QString data, int number_process){

    data.remove('\r'); //remove returns
    QStringList lines = data.split('\n');

    int process_counter = 0;
    int start = 0;

    int iterator = 0;

    for(QString line : lines){
        if(line.compare("<process>")){
         process_counter++;
         if(process_counter == number_process){
             start = iterator;
             break;
         }
        }
    }

    QString process_data = "";

    for(int i = start; i < lines.size(); i++){
        process_data += lines[i] + "\n";
    }

    return Process(QDate::fromString(get_xml_value_from_data(process_data, "<start-date>")),
                       QDate::fromString(get_xml_value_from_data(process_data, "<end-date>")),
                       get_xml_value_from_data(process_data, "<name>"),
                       get_xml_value_from_data(process_data, "<responsible>"),
                       get_xml_value_from_data(process_data, "<pstate>"));

}

QString FileDataHandler::get_process_data_from_project(Project p){

    QString content = "";

    for(Process* proc : p.get_processes()){

        content += "<process>\n";
        content += "<name>\n";
        content += proc->get_name() + "\n";
        content += "</name>\n";
        content += "<pstate>\n";

        if(proc->get_state().compare("TEMPLATE_STATE") == 0){
            content += "template\n";
        }else if(proc->get_state().compare("COMPLETED_STATE") == 0){
            content += "completed\n";
        }else{
            content += "open\n";
        }

        content += "</pstate>\n";
        content += "<responsible>\n";
        content += proc->get_responsible() + "\n";
        content += "</responsible>\n";
        content += "<time>\n";
        content += "<start-date>\n";
        content += proc->get_start_time().toString() + "\n";
        content += "</start-date>\n";
        content += "<end-date>\n";
        content += proc->get_end_time().toString() + "\n";
        content += "</time>\n";
        content += "</process>\n";
    }

    return content;
}

bool FileDataHandler::add_to_index(QString id){

    QString index = file_manager.get_file("index");
    index.remove('\r'); //remove returns

    QString source_list = get_xml_value_from_data(index, "<index>");

    int i = 0;
    while(!file_manager.set_to_file("index", "<index>\n<project-source>\n" + id +
                                    "</project-source>\n" + source_list + "\n</index>")){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(i++ > 10){
            return false;
        }
    }

    return true;
}

void FileDataHandler::set_source(QString source){
    file_manager.set_source(source);
}
