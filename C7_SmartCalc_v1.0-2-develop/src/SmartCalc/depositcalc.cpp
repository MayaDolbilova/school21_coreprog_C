#include "depositcalc.h"

#include "ui_depositcalc.h"

depositcalc::depositcalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::depositcalc) {
  ui->setupUi(this);
  connect(ui->res_dep, SIGNAL(clicked()), this,
          SLOT(on_deposit_credit_clicked()));
}

depositcalc::~depositcalc() { delete ui; }

void depositcalc::on_deposit_credit_clicked() {
  double sum = ui->sum_dep->text().toDouble();
  double time = ui->time_dep->text().toDouble();
  double percent_rate = ui->procent_dep->text().toDouble();
  double taxes_rate = 0.0;
  if (ui->taxes_dep->text().isEmpty()) {
    taxes_rate = 0.0;
  } else {
    taxes_rate = ui->taxes_dep->text().toDouble();
  }
  double sum_popolnenie = ui->sum_pop->text().toDouble();
  double sum_sniatie = ui->sum_snyat->text().toDouble();

  double month_popolnenie = ui->month_pop->text().toInt();
  double month_sniatie = ui->month_snyat->text().toInt();
  int capitalization = 0;
  if (ui->capitalization->isChecked()) {
    capitalization = 1;
  }
  int count = ui->comboBox->currentIndex();
  int interval_viplat = 0;
  if (count == 0)
    interval_viplat = 1;
  else if (count == 1)
    interval_viplat = 2;
  else if (count == 2)
    interval_viplat = 3;
  double percent = 0.0;
  double sum_nalog = 0.0;
  double percent_month = 0.0;
  double timer_monthes = 1.0;
  int div = div_rate(&interval_viplat, &time);
  if (sum > 0 && time > 0 && percent_rate > 0 && taxes_rate > 0) {
    for (int i = 1; i <= time; i++) {
      percent_month = sum * percent_rate / 100 / div;
      percent += percent_month;
      if (month_popolnenie > 0 && month_popolnenie == timer_monthes &&
          sum_popolnenie > 0) {
        sum += sum_popolnenie;
      }
      if (month_sniatie > 0 && month_sniatie == timer_monthes &&
          sum_sniatie > 0) {
        sum -= sum_sniatie;
      }
      if (capitalization == 1) {
        sum += percent_month;
      }
      if (interval_viplat == 1) {
        timer_monthes += 0.5;
      } else if (interval_viplat == 2) {
        timer_monthes += 0.25;
      } else if (interval_viplat == 3) {
        timer_monthes += 1;
      }
    }
    sum_nalog = tax_calc(percent, taxes_rate);
    ui->acc_perc->setText(QString::number(percent, 'f', 2));
    ui->sum_tax->setText(QString::number(sum_nalog, 'f', 2));
    ui->sum_in_end->setText(QString::number(sum, 'f', 2));
  }
}

int depositcalc::div_rate(int *period_viplat, double *deposit_term) {
  int div_rate = 0;
  if (*period_viplat == 1) {
    (*deposit_term) *= 30.65;
    div_rate = 365;
  } else if (*period_viplat == 2) {
    (*deposit_term) *= 4.33;
    div_rate = 52;
  } else if (*period_viplat == 3) {
    (*deposit_term) *= 1;
    div_rate = 12;
  }
  return div_rate;
}

double depositcalc::tax_calc(double final_percent_sum, double tax_rate) {
  double tax_amount = 0;
  double percent_stavka =
      0.12;  //на момент написания кода 12% это ключевая ставка ЦБ
  double neoblagaemaya_summa = 1000000 * percent_stavka;
  if (final_percent_sum > neoblagaemaya_summa) {
    double x = final_percent_sum -
               neoblagaemaya_summa;  //сумма которая облагается налогом
    tax_amount = x * (tax_rate / 100);
  } else {
    tax_amount = 0.0;
  }
  return tax_amount;
}
