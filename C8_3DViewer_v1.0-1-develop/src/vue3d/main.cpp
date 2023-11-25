#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  setlocale(LC_NUMERIC, "C");
  MainWindow window;
  window.show();
  return app.exec();
}
