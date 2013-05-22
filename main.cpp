
#include <resolvers/QtScriptResolver.h>
#include <jobview/JobStatusView.h>
#include <jobview/JobStatusModel.h>
#include <Pipeline.h>

#include <QApplication>
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    if( app.arguments().count() < 2 )
    {
        qDebug() << "Too few arguments passed";
        exit(-1);
    }

    //HACK: this really shouldn't be coupled so badly, you shouldn't need to init the job view just to use qtscriptresolver
    JobStatusView* jobsView = new JobStatusView( 0 );
    JobStatusModel* sourceModel = new JobStatusModel( jobsView );
    JobStatusSortModel* jobsModel = new JobStatusSortModel( jobsView );
    jobsModel->setJobModel( sourceModel );
    jobsView->setModel( jobsModel );

    QtScriptResolver* resolver = new QtScriptResolver( app.arguments().at(1) );

    // poc: you're able to init this here
    new Tomahawk::Pipeline( 0 );
}
