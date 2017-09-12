#ifndef PROJECTSTATE_H
#define PROJECTSTATE_H

#include <QString>

#include "state.h"

class OpenState;
class NearlyLateState;
class LateState;
class FinishedState;
class StockedState;

class ProjectState : public State
{
public:

    ProjectState() : State(){}

    virtual OpenState* set_open() = 0;
    virtual NearlyLateState* set_nearly_late() = 0;
    virtual LateState* set_late() = 0;
    virtual FinishedState* set_finished() = 0;
    virtual StockedState* set_stocked() = 0;

    virtual QString to_string() = 0;
};

class OpenState : public ProjectState
{
public:

    OpenState();

    NearlyLateState* set_nearly_late() override;
    LateState* set_late() override;
    FinishedState* set_finished() override;

    QString to_string() override;
};

class LateState : public ProjectState
{
public:

    LateState();

    OpenState* set_open() override;
    NearlyLateState* set_nearly_late() override;
    FinishedState* set_finished() override;

    QString to_string() override;
};

class NearlyLateState : public ProjectState
{
public:

    NearlyLateState();

    OpenState* set_open() override;
    LateState* set_late() override;
    FinishedState* set_finished() override;

    QString to_string() override;
};

class FinishedState : public ProjectState
{
public:

    FinishedState();

    OpenState* set_open() override;
    StockedState* set_stocked() override;

    QString to_string() override;
};

class StockedState : public ProjectState
{
public:

    StockedState();

    OpenState* set_open() override;

    QString to_string() override;
};

#endif // PROJECTSTATE_H
