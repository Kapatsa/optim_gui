#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "optinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Plot(QCustomPlot * customPlot);
    OptInfo opt;

private slots:


    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
