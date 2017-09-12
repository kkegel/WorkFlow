#ifndef PROCESSSTATE_H
#define PROCESSSTATE_H

#include <QString>

#include "state.h"

/**
 * @brief The ProcessState class
 *
 * the ProcessState is for managing the state of a process
 * its a child of state - what in particular doesnt matters
 *
 * ProcessState is only implemented by the Process class
 */

class ProcessState : public State
{
public:

    ProcessState() : State(){}

    virtual ProcessState* set_open() = 0;
    virtual ProcessState* set_late() = 0;
    virtual ProcessState* set_completed()= 0;
    virtual ProcessState* set_nearly_late() = 0;

    /**
     * @brief to_string
     * @return
     *
     * the class name as uppercase QString for identifing the state
     * by other classes (file backend, window frontend)
     */

    virtual QString to_string() = 0;

};

/**
 * @brief The TemplateState class
 *
 * in the template state, a process is created,
 * but no one opened it yet.
 * if a process is template, it can also switch to late or nearly late automatically.
 */

class _P_TemplateState : public ProcessState
{
public:

    _P_TemplateState();

    ProcessState* set_open() override;
    ProcessState* set_nearly_late() override;

    QString to_string() override;

};

/**
 * @brief The OpenState class
 *
 * the process is in work and the work is in time with 3 days befor deadline
 */

class _P_OpenState : public ProcessState
{
public:

    _P_OpenState();

    ProcessState* set_late() override;
    ProcessState* set_completed() override;
    ProcessState* set_nearly_late() override;

    QString to_string() override;

};

/**
 * @brief The LateState class
 *
 * the process is after deadline and not completed (or opened) yet.
 */

class _P_LateState : public ProcessState
{
public:

    _P_LateState();

    ProcessState* set_open() override;
    ProcessState* set_completed() override;
    ProcessState* set_nearly_late() override;

    QString to_string();

};

/**
 * @brief The _P_NearlyLateState class
 *
 * the process is 3 days before deadline (weekends are not counted)
 */

class _P_NearlyLateState : public ProcessState
{
public:

    _P_NearlyLateState();

    ProcessState* set_open() override;
    ProcessState* set_completed() override;
    ProcessState* set_late() override;

    QString to_string() override;

};

/**
 * @brief The CompletedState class
 *
 * the process is completed. over and out.
 */

class _P_CompletedState : public ProcessState
{
public:
    _P_CompletedState();

    QString to_string() override;
};

#endif // PROCESSSTATE_H
