#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDateTime>
#include <QDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QWidget>

#include "../libs/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  Ui::MainWindow *ui;

  /* VARIABLES FOR OPENGL LOGIC */
  bool isObjFile;
  int vertices_count;
  int edges_count;

  // ENUM MODES
  enum display_method { NONE, CIRCLE, SQUARE };
  enum projection_type { PARALLEL, CENTRAL };
  enum edges_type { SOLID, DASHED };

  ~MainWindow();

 private slots:
  void on_open_button_clicked();
  void save_settings();
  void load_settings();
  void make_gif();

  void on_pushButton_vertexColor_clicked();
  void on_gif_button_clicked();
  void on_snap_button_clicked();
  void on_horizontalSlider_Scale_valueChanged(int value);
  void on_radioButton_Parallel_clicked();
  void on_radioButton_Central_clicked();
  void on_radioButton_VertexNone_clicked();
  void on_radioButton_VertexCircle_clicked();
  void on_radioButton_VertexSquare_clicked();
  void on_horizontalSlider_VertexSize_valueChanged(int value);
  void on_radioButton_LineSolid_clicked();
  void on_radioButton_LineDashed_clicked();
  void on_horizontalSlider_LineSize_valueChanged(int value);
  void on_pushButton_lineColor_clicked();
  void on_pushButton_widgetColor_clicked();
  void on_horizontalSlider_rotX_valueChanged(int value);
  void on_horizontalSlider_rotY_valueChanged(int value);
  void on_horizontalSlider_rotZ_valueChanged(int value);
  void on_horizontalSlider_moveX_valueChanged(int value);
  void on_horizontalSlider_moveY_valueChanged(int value);
  void on_horizontalSlider_moveZ_valueChanged(int value);
  void on_spinBox_MoveX_valueChanged(int value);
  void on_spinBox_MoveY_valueChanged(int value);
  void on_spinBox_MoveZ_valueChanged(int value);
  void on_spinBox_rotX_valueChanged(int value);
  void on_spinBox_rotY_valueChanged(int value);
  void on_spinBox_rotZ_valueChanged(int value);
  void on_doubleSpinBox_LineSize_valueChanged(double value);
  void on_doubleSpinBox_VertexSize_valueChanged(double value);
  void on_reset_values_button_clicked();
  //  void on_horizontalSlider_Scale_sliderReleased();

 private:
  void set_mainwindow_attributes();
  void bind_slots();
  void restore_default_values();
  void on_projection_types_currentIndexChanged(int index);

  // Windows transition
  QPoint cur_pos;
  QPoint new_pos;
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  QSettings *settings;
  QString gif_name;
  QGifImage *gif_frame;
  int frames_counter = 0;
  QTimer *timer;
};
#endif  // MAINWINDOW_H
