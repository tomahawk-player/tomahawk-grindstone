
#include <resolvers/JSResolver.h>
#include <jobview/JobStatusView.h>
#include <jobview/JobStatusModel.h>
#include <Pipeline.h>

#include <QApplication>
#include <QDebug>
#include <QSettings>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    if( app.arguments().count() < 2 )
    {
        qDebug() << "Too few arguments passed";
        exit(-1);
    }

    // set application data for QSettings
    QCoreApplication::setOrganizationName( "Tomahawk" );
    QCoreApplication::setOrganizationDomain( "tomahawk-player.org" );
    QCoreApplication::setApplicationName( "Grindstone" );

    // init settings
    QSettings settings;

    // preset environment that is overwritten by --env if set
    QString environment = settings.value("defaultEnvironment", "default").toString();

    // parse --env argument
    QStringList arguments = app.arguments();
    arguments.takeFirst();
    for( int i=0; i<arguments.count(); i++ )
    {
        const QString arg = arguments[i];
        if( arg == "--env" && (i+1)<arguments.count() )
        {
            arguments.removeAt( i );
            environment = arguments.takeAt( i );
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

    JSResolver* resolver = new JSResolver( arguments.takeFirst(), arguments );

    // poc: you're able to init this here
    new Tomahawk::Pipeline( 0 );
}
