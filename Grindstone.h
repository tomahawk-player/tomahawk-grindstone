/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2013, Dominik Schmidt <domme@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRINDSTONE_H
#define GRINDSTONE_H

#include <QApplication>

class JSResolver;
class QMainWindow;

class Grindstone : public QApplication
{
Q_OBJECT

public:
    Grindstone( int& argc, char *argv[] );
    virtual ~Grindstone();

private slots:
    void onConfigDialogAccepted();

private:
    void quit();

    QMainWindow* m_mainWindow;
    JSResolver* m_resolver;
};

#endif // GRINDSTONE_H
