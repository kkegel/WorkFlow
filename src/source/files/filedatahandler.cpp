#include "../../header/filedatahandler.h"

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

std::vector<QString> FileDataHandler::get_stored_project_ids(){

    std::vector<QString> stored_ids;

    std::vector<QString> ids = get_all_project_ids();
    for(QString id : ids){
        if(get_xml_value_from_data(file_manager.get_file(id), "<state>").compare("stocked") == 0){
            stored_ids.push_back(id);
        }
    }

    return stored_ids;
}

bool FileDataHandler::set_project(Project p){

    QString p_id = p.get_id();
    QString old_id = "";
    if(p_id.section("",0,3).compare("#?#") == 0){
        QRegularExpression re("#\?#(.*?)#!#");
        QRegularExpressionMatch match = re.match(p_id);
        if (match.hasMatch()) {
            old_id = match.captured(0).section("",4,match.captured(0).size()-3);
            re = QRegularExpression("(?<=#!#).*$");
            match = re.match(p_id);
            p_id = match.captured(0);
        }
    }

    std::cout << p_id.toStdString() << std::endl;
    std::cout << old_id.toStdString() << std::endl;

    bool is_available = false;

    for(QString id : get_all_project_ids()){
         if(id.compare(p_id) == 0){
             is_available = true;
             break;
         }
    }

    if(!is_available){
        add_to_index(p_id);
    }

    p = Project(p.get_start_time(), p.get_end_time(), p_id, p.is_writable(), *(p.get_processes_p()), p.get_state_hint());
    return delete_project(old_id) && file_manager.set_to_file(p_id, build_data_from_project(p));
}

bool FileDataHandler::delete_project(QString id){

    QString index = file_manager.get_file("index");
    std::cout << index.toStdString() << std::endl;
    index = index.replace("<project-source>\n"+id+"\n</project-source>\n", "");
    std::cout << std::endl << index.toStdString() << std::endl;
    return file_manager.set_to_file("index", index);
}

Project FileDataHandler::build_project_from_data(QString data){

    int number_processes = get_number_elements_from_data(data, "<process>");
    std::vector<Process> processes;

    for(int i = 1; i <= number_processes; i++){
        processes.push_back(get_process_from_data(data, i));
    }

    bool writeable = false;
    if(get_xml_value_from_data(data, "<writeable>").toInt() == 1){
        writeable = true;
    }

    return Project(QDate::fromString(get_xml_value_from_data(data, "<start-time>")),
                       QDate::fromString(get_xml_value_from_data(data, "<end-time>")),
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
        state_hint = "stocked";
    }else{
        state_hint = "open";
    }

    QString data = QString("<project>\n")
              +  "<data>\n"
                 +  "<writeable>\n"
                    + writable + "\n"
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
                     +  "</start-time>\n"
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

QString FileDataHandler::get_xml_value_from_data(QString data, QString opening, int number){

    data.remove('\r'); //remove returns
    QStringList lines = data.split('\n');

    QString last = "";
    QString searched = "";

    bool opened = false;
    int n = 0;

    for(QString line : lines){
        if(line.compare(opening) == 0){
            if(n == number){
                opened = true;
                last = line;
                continue;
            }
            n++;
        }else if(opened && line.compare("</"+opening.mid(1,opening.size()-1)) == 0){
            break;
        }
        if(opened){
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

int FileDataHandler::get_number_elements_from_data(QString data, QString element){

    data.remove('\r'); //remove returns
    QStringList lines = data.split('\n');

    int number_elements = 0;

    for(QString line : lines){
        if(line.compare(element) == 0){
            number_elements++;
        }
    }

    return number_elements;
}

Process FileDataHandler::get_process_from_data(QString data, int number_process){

    data.remove('\r'); //remove returns
    QStringList lines = data.split('\n');

    int process_counter = 0;
    int start = 0;

    int iterator = 0;

    for(QString line : lines){
        if(line.compare("<process>") == 0){
            process_counter++;
            if(process_counter == number_process){
                start = iterator;
                break;
            }
        }
        iterator++;
    }

    QString process_data = "";

    for(int i = start; i < lines.size(); i++){
        process_data += lines[i] + "\n";
    }

    return Process(QDate::fromString(get_xml_value_from_data(process_data, "<start-date>")),
                       QDate::fromString(get_xml_value_from_data(process_data, "<end-date>")),
                       get_xml_value_from_data(process_data, "<name>"),
                       get_xml_value_from_data(process_data, "<responsible>"),
                       get_xml_value_from_data(process_data, "<pstate>"),
                       get_xml_value_from_data(process_data, "<annotation>").replace('$','\n'));

}

QString FileDataHandler::get_process_data_from_project(Project p){

    QString content = "";

    for(Process* proc : p.get_processes()){

        content += "<process>\n";
        content += "<name>\n";
        content += proc->get_name() + "\n";
        content += "</name>\n";
        content += "<pstate>\n";

        if(proc->get_state().compare("COMPLETED_STATE") == 0){
            content += "completed\n";
        }else if(proc->get_state().compare("TEMPLATE_STATE") == 0 || !proc->STARTED){
            content += "template\n";
        }else{
            content += "open\n";
        }

        content += "</pstate>\n";
        content += "<responsible>\n";
        content += proc->get_responsible() + "\n";
        content += "</responsible>\n";
        content += "<annotation>\n";
        content += proc->get_annotation().replace('\n','$') + "\n";
        content += "</annotation>\n";
        content += "<time>\n";
        content += "<start-date>\n";
        content += proc->get_start_time().toString() + "\n";
        content += "</start-date>\n";
        content += "<end-date>\n";
        content += proc->get_end_time().toString() + "\n";
        content += "</end-date>\n";
        content += "</time>\n";
        content += "</process>\n";
    }

    return content;
}

bool FileDataHandler::add_to_index(QString id){

    QString index = file_manager.get_file("index");
    index.remove('\r'); //remove returns

    QString source_list = get_xml_value_from_data(index, "<index>");

    QString seq_P = "\n";
    if(source_list.size() == 0){
        seq_P = "";
    }

    int i = 0;
    while(!file_manager.set_to_file("index", "<index>\n<project-source>\n" + id +
                                    "\n</project-source>\n" + source_list + seq_P + "</index>")){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(i++ > 10){
            return false;
        }
    }

    return true;
}

void FileDataHandler::set_user(std::vector<QString> users){

    QString content = "<user>\n";

    for(QString u : users){
        content += "<name>\n";
        content += u + "\n";
        content += "</name>\n";
    }
    content += "</user>";

    file_manager.set_to_file("__userdata", content);
}

std::vector<QString> FileDataHandler::get_user(){

    QString data = file_manager.get_file("__userdata");
    int number = get_number_elements_from_data(data, "<name>");

    std::vector<QString> user;

    for(int i = 0; i < number; i++){
        user.push_back(get_xml_value_from_data(data, "<name>", i));
    }
    return user;
}

void FileDataHandler::set_source(QString source){
    file_manager.set_source(source);
}
