#ifndef COMMANDER_H
#define COMMANDER_H

#include <QString>
#include <QStringList>
#include <QErrorMessage>

#include <vector>

/*
 * commands:
 *
 * nutzer-hinzufügen Name
 * nutzer-löschen Name
 * nutzer-anzeigen alle
 * nutzer-anzeigen Name
 */

class Commander
{
public:

    Commander(){}

    QStringList execute_command(QString command);

private:

    QStringList split_command(QString command);

};

#endif // COMMANDER_H
