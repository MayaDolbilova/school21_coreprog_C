#include "mainwindow.h"

#include "creditcalc.h"
#include "depositcalc.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(press_button()));
  connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_29, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_30, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_31, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_32, SIGNAL(clicked()), this, SLOT(press_mod()));
  connect(ui->pushButton_33, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_34, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_35, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_36, SIGNAL(clicked()), this, SLOT(press_func()));
  connect(ui->pushButton_39, SIGNAL(clicked()), this, SLOT(press_func()));

  connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(press_delete()));
  connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(press_ac()));
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(press_graph()));
  connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(press_cred()));
  connect(ui->pushButton_38, SIGNAL(clicked()), this, SLOT(press_depos()));
  connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(press_eq()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::press_button() {
  QPushButton *button = (QPushButton *)sender();

  if (ui->result->text().isEmpty()) {
    ui->result->setText(button->text());
  } else {
    ui->result->setText(ui->result->text() + button->text());
  }
}

void MainWindow::press_delete() {
  QString str = ui->result->text();
  if (!str.isEmpty()) {
    str.chop(1);
  }
  ui->result->setText(str);
}

void MainWindow::press_ac() { ui->result->setText(""); }
void MainWindow::press_mod() {
  QPushButton *button = (QPushButton *)sender();

  if (ui->result->text().isEmpty()) {
    ui->result->setText(button->text());
  } else {
    ui->result->setText(ui->result->text() + ' ' + button->text() + ' ');
  }
}

void MainWindow::press_func() {
  QPushButton *button = (QPushButton *)sender();
  ui->result->setText(ui->result->text() + button->text() + "(");
}

void MainWindow::press_eq() {
  char *inputstring = new char(ui->result->text().length());
  QByteArray barr = ui->result->text().toLatin1();
  strlcpy(inputstring, barr, ui->result->text().length() + 1);

  char *number_x = new char(ui->x_value->text().length());
  QByteArray barr_of_x = ui->x_value->text().toLatin1();
  strlcpy(number_x, barr_of_x, ui->x_value->text().length() + 1);

  if (ui->result->text().contains('x') &&
      (ui->x_value->text().length() == 0 || !ui->x_value->text().toDouble())) {
    QMessageBox::critical(this, "error", "Некорректный ввод x");
  } else {
    double result = 0.0;
    int error = calculator(inputstring, number_x, &result);

    if (error == 0) {
      QString valueAsString = QString::number(result, 'g', 15);
      ui->result->setText(valueAsString);
    } else if (error == 1) {
      QMessageBox::critical(this, "error", "Некорректный ввод");
    } else if (error == 2) {
      QMessageBox::critical(this, "error", "В Выражении более 255 символов");
    }
  }
  delete (inputstring);
  delete (number_x);
}

void MainWindow::press_graph() {
  ui->widget->clearGraphs();
  std::string str1 = ui->result->text().toStdString();
  const char *str = str1.c_str();
  double x_begin, x_end, y_begin, y_end;
  if (ui->min_x->text().isEmpty()) {
    x_begin = -5.0;
  } else {
    x_begin = ui->min_x->text().toDouble();
  }
  if (ui->max_x->text().isEmpty()) {
    x_end = 5;
  } else {
    x_end = ui->max_x->text().toDouble();
  }
  if (ui->min_y->text().isEmpty()) {
    y_begin = -5;
  } else {
    y_begin = ui->min_y->text().toDouble();
  }

  if (ui->max_y->text().isEmpty()) {
    y_end = 5;
  } else {
    y_end = ui->max_y->text().toDouble();
  }
  ui->widget->xAxis->setRange(x_begin, x_end);
  ui->widget->yAxis->setRange(y_begin, y_end);
  if (x_begin < x_end && y_begin < y_end) {
    double h = 0.01;
    int N = (x_end - x_begin) / h + 2;
    QVector<double> x(N), y(N);
    int i = 0;
    int error = 0;
    float X = 0.0;
    for (X = x_begin; X <= x_end; X += h) {
      double res = 0.0;
      QString floatString =
          QString::number(X);  // Преобразование float в QString
      char *x_calc = new char[floatString.length() +
                              1];  // Выделение памяти для массива символов
      qstrcpy(x_calc, floatString.toUtf8().constData());
      error = calculator((char *)str, x_calc, &res);
      delete[] x_calc;
      if (error == 0) {
        x[i] = X;
        y[i] = res;
        i++;
      }
    }
    if (error == 0) {
      ui->widget->addGraph();
      ui->widget->graph(0)->setData(x, y);
      ui->widget->graph(0)->setPen(QColor(255, 20, 147));
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
      ui->widget->replot();
      x.clear();
      y.clear();
    } else
      ui->result->setText("error");
  }
}

void MainWindow::press_cred() {
  CreditCalc window;
  window.setModal(true);
  window.exec();
}

void MainWindow::press_depos() {
  depositcalc window;
  window.setModal(true);
  window.exec();
}
