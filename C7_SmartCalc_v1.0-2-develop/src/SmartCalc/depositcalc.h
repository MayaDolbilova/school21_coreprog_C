#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <QDialog>
#include <QWidget>
namespace Ui {
class depositcalc;
}

class depositcalc : public QDialog {
  Q_OBJECT;

 public:
  explicit depositcalc(QWidget *parent = nullptr);
  ~depositcalc();
 private slots:
  void on_deposit_credit_clicked();
  int div_rate(int *period_viplat, double *deposit_term);
  double tax_calc(double final_percent_sum, double tax_rate);

 private:
  double snyat, popoln;
  Ui::depositcalc *ui;
};

#endif  // DEPOSITCALC_H
