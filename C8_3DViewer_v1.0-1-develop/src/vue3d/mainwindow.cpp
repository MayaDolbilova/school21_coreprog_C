#include "mainwindow.h"

#include "./glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  set_mainwindow_attributes();
  bind_slots();
  settings = new QSettings("School 21", "Vue 3D", this);
  load_settings();
}

MainWindow::~MainWindow() {
  save_settings();
  destroy_object(&ui->OpenGlWidget->data);
  delete settings;
  delete ui;
}

void MainWindow::set_mainwindow_attributes() {
  this->setWindowTitle(
      "Vue 3D [A basic 3D Viewer project by @lostnola, @jereninf and "
      "@rosamonj]");
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setAutoFillBackground(true);
  timer = new QTimer(0);
}

void MainWindow::bind_slots() {
  connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
}

void MainWindow::restore_default_values() {
  ui->horizontalSlider_Scale->setValue(50);
  ui->horizontalSlider_rotX->setValue(0);
  ui->horizontalSlider_rotY->setValue(0);
  ui->horizontalSlider_rotZ->setValue(0);
  ui->horizontalSlider_moveX->setValue(0);
  ui->horizontalSlider_moveY->setValue(0);
  ui->horizontalSlider_moveZ->setValue(0);
}

void MainWindow::save_settings() {
  settings->setValue("are_settings", 1);
  settings->setValue("projection_type", ui->OpenGlWidget->projection_type);
  settings->setValue("v_display_method", ui->OpenGlWidget->v_display_method);
  settings->setValue("vertices_size", ui->OpenGlWidget->vertices_size);
  settings->setValue("v_red", ui->OpenGlWidget->v_red);
  settings->setValue("v_green", ui->OpenGlWidget->v_green);
  settings->setValue("v_blue", ui->OpenGlWidget->v_blue);
  settings->setValue("edges_type", ui->OpenGlWidget->edges_type);
  settings->setValue("edges_thickness", ui->OpenGlWidget->edges_thickness);
  settings->setValue("e_red", ui->OpenGlWidget->e_red);
  settings->setValue("e_green", ui->OpenGlWidget->e_green);
  settings->setValue("e_blue", ui->OpenGlWidget->e_blue);
  settings->setValue("bg_red", ui->OpenGlWidget->bg_red);
  settings->setValue("bg_green", ui->OpenGlWidget->bg_green);
  settings->setValue("bg_blue", ui->OpenGlWidget->bg_blue);
}

void MainWindow::load_settings() {
  if (settings->value("are_settings").toInt()) {
    char rgba_color[40];
    ui->radioButton_Parallel->setChecked(true);
    int v_mode = settings->value("v_display_method").toInt();
    if (v_mode == 0) {
      ui->radioButton_VertexNone->setChecked(true);
      ui->OpenGlWidget->v_display_method = 0;
    } else if (v_mode == 1) {
      ui->radioButton_VertexCircle->setChecked(true);
      ui->OpenGlWidget->v_display_method = 1;
    } else if (v_mode == 2) {
      ui->radioButton_VertexSquare->setChecked(true);
      ui->OpenGlWidget->v_display_method = 2;
    }
    ui->doubleSpinBox_VertexSize->setValue(
        settings->value("vertices_size").toInt());
    ui->horizontalSlider_VertexSize->setValue(
        settings->value("vertices_size").toInt());
    ui->OpenGlWidget->v_red = settings->value("v_red").toDouble();
    ui->OpenGlWidget->v_green = settings->value("v_green").toDouble();
    ui->OpenGlWidget->v_blue = settings->value("v_blue").toDouble();
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)",
            (int)(ui->OpenGlWidget->v_red * 255),
            (int)(ui->OpenGlWidget->v_green * 255),
            (int)(ui->OpenGlWidget->v_blue * 255));
    ui->label_vertexColor->setStyleSheet(rgba_color);
    int edges_mode = settings->value("edges_type").toInt();
    if (edges_mode == 0) {
      ui->radioButton_LineSolid->setChecked(true);
      ui->OpenGlWidget->edges_type = 0;
    } else if (edges_mode == 1) {
      ui->radioButton_LineDashed->setChecked(true);
      ui->OpenGlWidget->edges_type = 1;
    }
    ui->doubleSpinBox_LineSize->setValue(
        settings->value("edges_thickness").toInt() * 10);
    ui->horizontalSlider_LineSize->setValue(
        settings->value("edges_thickness").toInt() * 10);
    ui->OpenGlWidget->e_red = settings->value("e_red").toDouble();
    ui->OpenGlWidget->e_green = settings->value("e_green").toDouble();
    ui->OpenGlWidget->e_blue = settings->value("e_blue").toDouble();
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)",
            (int)(ui->OpenGlWidget->e_red * 255),
            (int)(ui->OpenGlWidget->e_green * 255),
            (int)(ui->OpenGlWidget->e_blue * 255));
    ui->label_lineColor->setStyleSheet(rgba_color);
    ui->OpenGlWidget->bg_red = settings->value("bg_red").toDouble();
    ui->OpenGlWidget->bg_green = settings->value("bg_green").toDouble();
    ui->OpenGlWidget->bg_blue = settings->value("bg_blue").toDouble();
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)",
            (int)(ui->OpenGlWidget->bg_red * 255),
            (int)(ui->OpenGlWidget->bg_green * 255),
            (int)(ui->OpenGlWidget->bg_blue * 255));
    ui->label_backgroundColor->setStyleSheet(rgba_color);
  }
}

void MainWindow::on_open_button_clicked() {
  restore_default_values();
  QDir::setCurrent(QCoreApplication::applicationDirPath());
  QDir dir(QDir::currentPath());
  dir.cdUp();
  dir.cd("objects");
  QString dataSamplesDir = dir.absolutePath();
  QString filePath = QFileDialog::getOpenFileName(
      this, "Choose file", dataSamplesDir, ".obj (*.obj)");
  if (filePath.isEmpty()) {
    QMessageBox::information(
        nullptr, "File error",
        "The file has not been selected or the file is not an .obj");
  } else {
    ui->OpenGlWidget->filename = filePath.toLatin1().data();
    ui->OpenGlWidget->parse_obj();
    if (ui->OpenGlWidget->filename[0] != '\0') {
      isObjFile = 1;
      char *start = strrchr(filePath.toLatin1().data(), '/') + 1;
      char *ext = strrchr(filePath.toLatin1().data(), '.');
      *ext = '\0';
      ui->label_name->setText(start);
    } else {
      isObjFile = 0;
    }
  }

  ui->label_vertex->setText(
      QString::number(ui->OpenGlWidget->data.vertices_count));
  ui->label_polygons->setText(
      QString::number(ui->OpenGlWidget->data.polygons_count / 2));
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  move(x() + new_pos.x(), y() + new_pos.y());
  cur_pos = event->globalPosition().toPoint();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}

void MainWindow::on_projection_types_currentIndexChanged(int index) {
  if (index == 0) {
    ui->OpenGlWidget->projection_type = PARALLEL;
  } else if (index == 1) {
    ui->OpenGlWidget->projection_type = CENTRAL;
  }
  ui->OpenGlWidget->update();
}

void MainWindow::on_pushButton_vertexColor_clicked() {
  QColor initialColor = QColor(242, 165, 60);
  QColor myColor = QColorDialog::getColor(initialColor, this, "Choose Color");

  if (myColor.isValid()) {
    ui->OpenGlWidget->v_red = myColor.redF();
    ui->OpenGlWidget->v_green = myColor.greenF();
    ui->OpenGlWidget->v_blue = myColor.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", myColor.red(),
            myColor.green(), myColor.blue());
    ui->pushButton_vertexColor->setStyleSheet(rgba_color);
    ui->label_vertexColor->setStyleSheet(rgba_color);
    ui->OpenGlWidget->update();
  }
}

void MainWindow::on_radioButton_VertexNone_clicked() {
  ui->OpenGlWidget->v_display_method = NONE;
  ui->OpenGlWidget->update();
}

void MainWindow::on_radioButton_VertexCircle_clicked() {
  ui->OpenGlWidget->v_display_method = CIRCLE;
  ui->OpenGlWidget->update();
}

void MainWindow::on_radioButton_VertexSquare_clicked() {
  ui->OpenGlWidget->v_display_method = SQUARE;
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_VertexSize_valueChanged(int value) {
  ui->OpenGlWidget->vertices_size = value / 2;
  ui->doubleSpinBox_VertexSize->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_radioButton_LineSolid_clicked() {
  ui->OpenGlWidget->edges_type = SOLID;
  ui->OpenGlWidget->update();
}

void MainWindow::on_radioButton_LineDashed_clicked() {
  ui->OpenGlWidget->edges_type = DASHED;
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_LineSize_valueChanged(int value) {
  ui->OpenGlWidget->edges_thickness = value / 10;
  ui->doubleSpinBox_LineSize->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_pushButton_lineColor_clicked() {
  QColor edge_color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (edge_color.isValid()) {
    ui->OpenGlWidget->e_red = edge_color.redF();
    ui->OpenGlWidget->e_green = edge_color.greenF();
    ui->OpenGlWidget->e_blue = edge_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", edge_color.red(),
            edge_color.green(), edge_color.blue());
    ui->label_lineColor->setStyleSheet(rgba_color);
    ui->pushButton_lineColor->setStyleSheet(rgba_color);
    ui->OpenGlWidget->update();
  }
}

void MainWindow::on_pushButton_widgetColor_clicked() {
  QColor bg_color = QColorDialog::getColor(Qt::white, this, "Choose color");
  if (bg_color.isValid()) {
    ui->OpenGlWidget->bg_red = bg_color.redF();
    ui->OpenGlWidget->bg_green = bg_color.greenF();
    ui->OpenGlWidget->bg_blue = bg_color.blueF();
    char rgba_color[40];
    sprintf(rgba_color, "background-color: rgb(%d,%d,%d)", bg_color.red(),
            bg_color.green(), bg_color.blue());
    ui->label_backgroundColor->setStyleSheet(rgba_color);
    ui->pushButton_widgetColor->setStyleSheet(rgba_color);
    ui->OpenGlWidget->update();
  }
}

void MainWindow::on_horizontalSlider_Scale_valueChanged(int value) {
  if (&ui->OpenGlWidget->data != NULL) {
    double val = 1.0 + (value - ui->OpenGlWidget->scale_val) * 0.01;
    if (val < 0.1) {
      val = 0.1;
    }
    scale_object(&ui->OpenGlWidget->data, val);
    ui->OpenGlWidget->scale_val = value;
    ui->OpenGlWidget->update();
  }
}

void MainWindow::on_horizontalSlider_rotX_valueChanged(int value) {
  rotate_X(&ui->OpenGlWidget->data, (value - ui->OpenGlWidget->rotate_x));
  ui->OpenGlWidget->rotate_x = value;
  ui->spinBox_rotX->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_rotY_valueChanged(int value) {
  rotate_Y(&ui->OpenGlWidget->data, (value - ui->OpenGlWidget->rotate_y));
  ui->OpenGlWidget->rotate_y = value;
  ui->spinBox_rotY->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_rotZ_valueChanged(int value) {
  rotate_Z(&ui->OpenGlWidget->data, (value - ui->OpenGlWidget->rotate_z));
  ui->OpenGlWidget->rotate_z = value;
  ui->spinBox_rotZ->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_moveX_valueChanged(int value) {
  shift_X(&ui->OpenGlWidget->data, (value - ui->OpenGlWidget->translate_x) *
                                       ui->OpenGlWidget->norm_ratio / 100);
  ui->OpenGlWidget->translate_x = value;
  ui->spinBox_MoveX->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_moveY_valueChanged(int value) {
  shift_Y(&ui->OpenGlWidget->data, (value - ui->OpenGlWidget->translate_y) *
                                       ui->OpenGlWidget->norm_ratio / 100);
  ui->OpenGlWidget->translate_y = value;
  ui->spinBox_MoveY->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_horizontalSlider_moveZ_valueChanged(int value) {
  shift_Z(&ui->OpenGlWidget->data, (value - ui->OpenGlWidget->translate_z) *
                                       ui->OpenGlWidget->norm_ratio / 100);
  ui->OpenGlWidget->translate_z = value;
  ui->spinBox_MoveZ->setValue(value);
  ui->OpenGlWidget->update();
}

void MainWindow::on_snap_button_clicked() {
  if (isObjFile) {
    QFileDialog dialogConnectImage(this);
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Shot " + formattedTime + ".jpeg";
    QString image_name = dialogConnectImage.getSaveFileName(
        this, tr("Save a screenshot"), name_pattern,
        tr("image (*.jpeg *.bmp)"));
    if (image_name.length() >= 1) {
      QImage img = ui->OpenGlWidget->grabFramebuffer();
      img.save(image_name);
      QMessageBox messageBoxImage;
      messageBoxImage.information(0, "", "Screenshot saved successfully");
    }
  } else {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please open .obj file to take a screenshot");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void MainWindow::on_gif_button_clicked() {
  if (isObjFile) {
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Cast " + formattedTime + ".gif";
    gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                            name_pattern, tr("gif (*.gif)"));
    if (gif_name != "") {
      ui->gif_button->setDisabled(true);
      gif_frame = new QGifImage;
      gif_frame->setDefaultDelay(10);
      timer->setInterval(100);
      timer->start();
    }
  } else {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please open .obj file to take a screencast");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void MainWindow::make_gif() {
  QImage image = ui->OpenGlWidget->grabFramebuffer();
  QSize image_size(640, 480);
  QImage scaled_image = image.scaled(image_size);
  gif_frame->addFrame(scaled_image);
  if (frames_counter == 50) {
    timer->stop();
    gif_frame->save(gif_name);
    frames_counter = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif animation saved successfully");
    delete gif_frame;
    ui->gif_button->setText("");
    ui->gif_button->setEnabled(true);
  }
  frames_counter++;
  if (!ui->gif_button->isEnabled()) {
    ui->gif_button->setText(QString::number(frames_counter / 10) + "s");
  }
}

void MainWindow::on_radioButton_Parallel_clicked() {
  on_projection_types_currentIndexChanged(0);
}

void MainWindow::on_radioButton_Central_clicked() {
  on_projection_types_currentIndexChanged(1);
}

void MainWindow::on_spinBox_MoveX_valueChanged(int value) {
  ui->horizontalSlider_moveX->setValue(value);
}

void MainWindow::on_spinBox_MoveY_valueChanged(int value) {
  ui->horizontalSlider_moveY->setValue(value);
}

void MainWindow::on_spinBox_MoveZ_valueChanged(int value) {
  ui->horizontalSlider_moveZ->setValue(value);
}

void MainWindow::on_spinBox_rotX_valueChanged(int value) {
  ui->horizontalSlider_rotX->setValue(value);
}

void MainWindow::on_spinBox_rotY_valueChanged(int value) {
  ui->horizontalSlider_rotY->setValue(value);
}

void MainWindow::on_spinBox_rotZ_valueChanged(int value) {
  ui->horizontalSlider_rotZ->setValue(value);
}

void MainWindow::on_doubleSpinBox_LineSize_valueChanged(double value) {
  ui->horizontalSlider_LineSize->setValue(value);
}

void MainWindow::on_doubleSpinBox_VertexSize_valueChanged(double value) {
  ui->horizontalSlider_VertexSize->setValue(value);
}

void MainWindow::on_reset_values_button_clicked() { restore_default_values(); }

// void MainWindow::on_horizontalSlider_Scale_sliderReleased()
//{
//     if (&ui->OpenGlWidget->data != NULL) {
//     int value = ui->horizontalSlider_Scale->value();
//     double val = 1.0 + (value - ui->OpenGlWidget->scale_val) * 0.01;
//     if (val < 0.1) {
//       val = 0.1;
//     }
//     scale_object(&ui->OpenGlWidget->data, val);
//     ui->OpenGlWidget->scale_val = value;
//     ui->OpenGlWidget->update();
//     }
// }
