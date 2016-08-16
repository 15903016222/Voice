#include "mainwindow.h"
#include <QApplication>

#include <QDir>
#include <QGst/Init>
#include <QGlib/Error>
#include <gst/gstregistry.h>

void dopplink_init_gst(int argc, char *argv[])
{

  if(argc > 0)
  {
    try{
      QGst::init( &argc, &argv);
    }catch(QGlib::Error &error){
      qFatal("FIXME: init gstreamer failed.");
    }

    QDir plugin_search_dir(qApp->applicationDirPath());

    plugin_search_dir.cdUp();
    plugin_search_dir.cd("gst_plugins");

    qDebug("plugins: %s", plugin_search_dir.absolutePath().toUtf8().data());

    gst_registry_scan_path(gst_registry_get(), plugin_search_dir.absolutePath().toUtf8().data());

  } else {
    // FIXME: error handle
  }
}

int main(int argc, char *argv[])
{
  int r = 0;
  QApplication a(argc, argv);
  dopplink_init_gst(argc, argv);

  {
    MainWindow w;
    w.show();

    r = a.exec();
  }

  QGst::cleanup();

  return r;
}
