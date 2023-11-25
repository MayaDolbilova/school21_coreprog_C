#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
extern "C" {
#include "../s21_smartcal.h"
}
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double x_begin, x_end, y_begin, y_end, h;
  int N;
 private slots:
  void press_button();
  void press_func();
  void press_ac();
  void press_delete();
  void press_eq();
  void press_graph();
  void press_cred();
  void press_depos();
  void press_mod();
};

#endif  // MAINWINDOW_H
