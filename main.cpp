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

#include "Grindstone.h"

#include <QCoreApplication>
#include <QStringList>
#include <QDebug>

int main(int argc, char **argv)
{
    // set application data for QSettings
    QCoreApplication::setOrganizationName( "Tomahawk" );
    QCoreApplication::setOrganizationDomain( "tomahawk-player.org" );
    QCoreApplication::setApplicationName( "Grindstone" );

    Grindstone app(argc, argv);

    return app.exec();
}
