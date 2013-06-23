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
#include "ResolverDialog.h"

#include <accounts/AccountConfigWidget.h>
#include <jobview/JobStatusView.h>
#include <jobview/JobStatusModel.h>
#include <resolvers/JSResolver.h>
#include <utils/Logger.h>
#include <Pipeline.h>

#include <QDebug>
#include <QSettings>
#include <QMainWindow>
#include <QStringList>
#include <QApplication>

Grindstone::Grindstone(int& argc, char* argv[])
    : QApplication( argc, argv )
    , m_mainWindow( new QMainWindow() )
{
    if( arguments().count() < 2 )
    {
        qDebug() << "Too few arguments passed";
        exit(-1);
    }

    // init settings
    QSettings settings;

    // preset environment that is overwritten by --env if set
    QString environment = settings.value("defaultEnvironment", "default").toString();
    bool showConfig = false;

    // parse --env argument
    QStringList arguments = QCoreApplication::instance()->arguments();
    arguments.takeFirst();
    for( int i=0; i<arguments.count(); i++ )
    {
        const QString arg = arguments[i];

        if( arg == "--env" && (i+1)<arguments.count() )
        {
            arguments.removeAt( i );
            environment = arguments.takeAt( i );
        }

        if( arg == "--config" )
        {
            arguments.removeAt( i );
            showConfig = true;
        }
    }

    // tell the user what env is used now
    qDebug() << "Running in Environment:" << environment;


    // load tomahawkjsPath from settings file
    settings.beginGroup( QString( "env_%1" ).arg( environment ) );
    QString tomahawkjsPath = settings.value( "tomahawkjsPath" ).toString();
    settings.endGroup();

    // add the tomahawkksPath to the JSResolver arguments
    if( tomahawkjsPath.isNull() )
    {
        qDebug() << "**********************************************************************";
        qDebug() << "No default tomahawk.js in this env.";
        qDebug() << "Make sure it's passed as additional path to Grindstone!";
        qDebug() << "You can add a default one by adding";
        qDebug() << "";
        qDebug() << QString("[env_%1]"
                            "\ntomahawkjsPath=/home/haxX0r/pathToYour/tomahawk.js"
                    ).arg( environment );
        qDebug() << "";
        qDebug() << "to your Grindstone.conf";
        qDebug() << "**********************************************************************";
    }
    else
    {
        qDebug() << "Found default tomahawkjs for this env: " << tomahawkjsPath;
        arguments << tomahawkjsPath;
    }

    //HACK: this really shouldn't be coupled so badly, you shouldn't need to init the job view just to use JSresolver
    JobStatusView* jobsView = new JobStatusView( 0 );
    JobStatusModel* sourceModel = new JobStatusModel( jobsView );
    JobStatusSortModel* jobsModel = new JobStatusSortModel( jobsView );
    jobsModel->setJobModel( sourceModel );
    jobsView->setModel( jobsModel );

    // poc: you're able to init this here - also we need it to start the resolver ...
    new Tomahawk::Pipeline( 0 );

    m_resolver = new JSResolver( arguments.takeFirst(), arguments );
    m_resolver->start();


    if( !m_resolver->running() )
    {
        qDebug() << "Resolver not running, exiting.";
        ::exit( -1 );
    }

    if( showConfig )
    {
         tLog() << "Show config widget";

        ResolverDialog* dialog = new ResolverDialog(m_resolver);
        dialog->show();

        connect(dialog, SIGNAL( accepted() ), SLOT( onConfigDialogAccepted() ) );
        connect(dialog, SIGNAL(rejected() ), QCoreApplication::instance(), SLOT( quit() ) );
    }
}


Grindstone::~Grindstone()
{

}


void
Grindstone::onConfigDialogAccepted()
{
    m_resolver->saveConfig();

    // wtf ... webkit needs some time to save the config ....
    QTimer::singleShot( 2000, QCoreApplication::instance(), SLOT( quit() ) );
}
