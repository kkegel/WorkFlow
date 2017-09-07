#ifndef PROJECTSTATE_H
#define PROJECTSTATE_H

#include <QString>

#include "state.h"

class ProjectState : public State
{
public:

    ProjectState();

    ProjectState set_open();
    ProjectState set_nearly_late();
    ProjectState set_late();
    ProjectState set_finished();
    ProjectState set_stocked();

    virtual QString to_string();
};

class OpenState : public ProjectState
{
public:

    OpenState();

    ProjectState set_nearly_late();
    ProjectState set_late();
    ProjectState set_finished();

    QString to_string();
};

class LateState : public ProjectState
{
public:

    LateState();

    ProjectState set_open();
    ProjectState set_nearly_late();
    ProjectState set_finished();

    QString to_string();
};

class NearlyLateState : public ProjectState
{
public:

    NearlyLateState();

    ProjectState set_open();
    ProjectState set_late();
    ProjectState set_finished();

    QString to_string();
};

class FinishedState : public ProjectState
{
public:

    FinishedState();

    ProjectState set_open();
    ProjectState set_stocked();

    QString to_string();
};

class StockedState : public ProjectState
{
public:

    StockedState();

    ProjectState set_open();

    QString to_string();
};

#endif // PROJECTSTATE_H
