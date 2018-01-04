# WorkFlow - Project Management

## License

project under GNU GPLv3 - you find a licence copy in this repository.
note the use of the QT framework https://www.qt.io also under under GPL & LGPLv3 licenses and its usage obligations.

## Overview

for detailed usage information, look at
[userguide](./USERGUIDE.md).

organize your team. organize your projects. now.
WorkFlow is an extremely lightweight solution to organize projects in teams and small companies.

what you need is no database, no webserver, only a small NAS Drive in your VPN/LAN network and thats enough.
and because it's local, it's save. every project you create, is your project, because you own its file on your drive.

to save data, WorkFlow uses simplyfied XML files, which are created automatically. the only thing you have to do is to select a directory, make it ready and start WorkFlow - thats all.
the best thing is, with WorkFlow, you can work with different Teams in different directories. just select another working dir within the WorkFlow app. with that simple technology, you can easyly handle acces rigths on your NAS - so WorkFlow don't have to care about such things and can stay simple and smart.

WorkFlow is written in C++/Qt

## Build Instructions

to build/compile WorkFlow you have to clone this repository first.
if you are already familiar with Qt, the src folder contains a WorkFlow.pro Qt project file you can use to build within your Qt environment.

if you don't have used Qt before, you have to install the framework librarys and tools first, then you can build as described.

for deployment, you have to use one of Qt's platform specific deployment tools. please note the Qt license descriptions therefore.

## Getting Started

for the following instructions, you should have compiled WorkFlow first.

1. open a directory you want tu use as a WorkFlow project directory
2. create a file ``index.xml`` and ``__userdata.xml`` within that directory
3. open ``index.xml`` and write the following lines (no additional tabs, spaces or newlines!)

   ```XML
<index>
</index>
```

4. open ``__userdata.xml`` and write the following lines. between ``<data>`` and ``</data>`` you can create as many users as you want. a user is not a user in the meaning of a authentication but as selectable person - so the number of users in the file and the number of 'real' users of WorkFlow can vary. in WorkFlow users are virtual persons beeing responsible for tasks. you have to create min. one user (note that the file is no default xml, so don't use additional tabs, spaces or newlines)
in the following example, a user with the name ``Secretary M. Fisher `` and a user with the name ``Office Workshop`` are created.

   ```XML
<data>
<user>
Secretary M. Fisher
</user>
<user>
Office Workshop
</user>
</data>
```

5. now, you can start WorkFlow -> go to Source -> select the ``index.xml`` -> restart the app -> everything will work. to select anothe working dir - just select an other index file.
