/**
  This file is part of WorkFlow.

  WorkFlow is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  WorkFlow is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

  Copyright (C) Karl Kegel (github: kkegel) 2018
*/

#include "../../header/process_.h"

Process::Process(QDate start_date, QDate end_date, QString name,
                 QString responsible, QString state_hint, QString annotation) :
    ProjectItem(start_date, end_date)
{
    this->NAME = name;
    this->responsible = responsible;
    this->annotation = annotation;

    determine_state(state_hint);
}

QString Process::get_name(){
    return NAME;
}

QString Process::get_title(){
    return get_name();
}

QString Process::get_responsible(){
    return responsible;
}

QString Process::get_annotation(){
    return annotation;
}

void Process::set_annotation(QString an){
    this->annotation = an;
}

void Process::determine_state(QString state_hint){

    if(state_hint.compare("completed") == 0){
        state = new _P_CompletedState();
        STARTED = false;
    }else{

        if(state_hint.compare("open") == 0){
            STARTED = true;
        }else{
            STARTED = false;
        }

        QDate today = QDate::currentDate();
        int day_count = 0;
        while(today.toJulianDay() <= END_TIME.toJulianDay()){
            if(today.dayOfWeek() < 6){
                day_count++;
            }
            today = today.addDays(1);
        }

        if(day_count <= 1){
            state = new _P_LateState();
        }else if(day_count <= 3){
            state = new _P_NearlyLateState();
        }else{

            if(state_hint.compare("template") == 0){
                state = new _P_TemplateState();
            }else{
                state = new _P_OpenState();
            }
        }
    }
}

bool Process::set_open(){
    state = state->set_open();
    return true;
}

bool Process::set_late(){
    state = state->set_late();
    return true;
}

bool Process::set_nearly_late(){
    state = state->set_nearly_late();
    return true;
}

bool Process::set_completed(){
    state = state->set_completed();
    return true;
}

QString Process::get_state(){
    if(state != NULL){
        return state->to_string();
    }
    return "";
}
