#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optinfo.h"
#include <iostream>
#include <string>
#include "qcustomplot.h"
//---------------
#include "Area.hpp"
#include "RectArea.hpp"
#include "OptMethod.hpp"
#include "GradDesc.hpp"
#include "Stochastic.hpp"
#include "StopCriterion.hpp"
#include "Abs.hpp"
#include "Function.hpp"
//---------------


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mousePos(QMouseEvent*)));
    connect(ui->plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mouseClick(QMouseEvent*)));
    opt.functionnumber = ui->comboBox->currentIndex();
    opt.rangeX1 = ui->doubleSpinBox->value();
    opt.rangeX2 = ui->doubleSpinBox_2->value();
    opt.rangeY1 = ui->doubleSpinBox_3->value();
    opt.rangeY2 = ui->doubleSpinBox_4->value();
    opt.method = ui->tabWidget->currentIndex();
    opt.stop_grad_method = ui->tabWidget_2->currentIndex();
    opt.stop_stoc_method = ui->radioButton->isChecked();
    opt.eps_grad = ui->eps_grad_grad->value();
    opt.eps_diff = ui->eps_diff_grad->value();
    opt.local_prob = ui->spinbox_prob->value();
    opt.maxIter = ui->spinBox_2->value();
    opt.x_0[0] = ui->x_0->value();
    opt.x_0[1] = ui->y_0->value();
    Plot(ui->plot);

}


void MainWindow::Plot(QCustomPlot * customPlot){
    // create graph and assign data to it:
    // configure axis rect:
      customPlot->clearPlottables();
      //customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
      customPlot->axisRect()->setupFullAxesBox(true);
      customPlot->xAxis->setLabel("x");
      customPlot->yAxis->setLabel("y");\

      //customPlot->xAxis->range() = QCPRange(opt.rangeX1, opt.rangeX2);

      // set up the QCPColorMap:
      QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
      int nx = 200;
      int ny = 200;


      colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
      colorMap->data()->setRange(QCPRange(opt.rangeX1, opt.rangeX2), QCPRange(opt.rangeY1, opt.rangeY2)); // and span the coordinate range
      // now we assign some data, by accessing the QCPColorMapData instance of the color map:
      double x, y, z;

      for (int xIndex=0; xIndex<nx; ++xIndex)
      {
        for (int yIndex=0; yIndex<ny; ++yIndex)
        {
          colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
          //double r = 3*qSqrt(x*x+y*y)+1e-2;
          //
          switch (opt.functionnumber){
                  case 0:
                    z = 0.1*cos(10*(x*x + y*y));
                    break;
                  case 1:
                    z = x+y;
                    break;
                  case 2:
                    z = (1-x)*(1-x) + 100*(y-x*x)*(y-x*x);
                    break;
          }
          colorMap->data()->setCell(xIndex, yIndex, z);
        }
      }

      // add a color scale:
      QCPColorScale *colorScale = new QCPColorScale(customPlot);
      customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
      colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
      colorMap->setColorScale(colorScale); // associate the color map with the color scale
      //colorScale->axis()->setLabel("Magnetic Field Strength");

      // set the color gradient of the color map to one of the presets:
      colorMap->setGradient(QCPColorGradient::gpPolar);
      // we could have also created a QCPColorGradient instance and added own colors to
      // the gradient, see the documentation of QCPColorGradient for what's possible.

      // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
      colorMap->rescaleDataRange();

      // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
      QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
      customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
      colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

      // rescale the key (x) and value (y) axes so the whole color map is visible:
      customPlot->rescaleAxes();
      customPlot->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    opt.rangeX1 = arg1;
    Plot(ui->plot);
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    opt.rangeX2 = arg1;
    Plot(ui->plot);
}

void MainWindow::on_doubleSpinBox_3_valueChanged(double arg1)
{
    opt.rangeY1 = arg1;
    Plot(ui->plot);
}

void MainWindow::on_doubleSpinBox_4_valueChanged(double arg1)
{
    opt.rangeY2 = arg1;
    Plot(ui->plot);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    opt.functionnumber = index;
    Plot(ui->plot);
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    //READ ALL INPUT FROM FIELDS
    opt.functionnumber = ui->comboBox->currentIndex();
    opt.rangeX1 = ui->doubleSpinBox->value();
    opt.rangeX2 = ui->doubleSpinBox_2->value();
    opt.rangeY1 = ui->doubleSpinBox_3->value();
    opt.rangeY2 = ui->doubleSpinBox_4->value();
    opt.method = ui->tabWidget->currentIndex();
    opt.stop_grad_method = ui->tabWidget_2->currentIndex();
    opt.stop_stoc_method = ui->radioButton->isChecked();
    opt.eps_grad = ui->eps_grad_grad->value();
    opt.eps_diff = ui->eps_diff_grad->value();
    opt.local_prob = ui->spinbox_prob->value();
    opt.maxIterAfterLastSuccess = ui->spinBox_3->value();
    opt.maxIter = ui->spinBox_2->value();
    opt.x_0[0] = ui->x_0->value();
    opt.x_0[1] = ui->y_0->value();

    //CREATE ALL INSTANCES FOR OPTIMIZATION

    //function
    Function *f;
    switch(opt.functionnumber){
        case 0:{
            f1 f1;
            f = &f1;
            break;
        }
        case 1:{
            f3 f3;
            f = &f3;
            break;
        }
        case 2:{
            f4 f4;
            f = &f4;
            break;
        }
    }

    //area
    long double range[4] = {opt.rangeX1, opt.rangeX2, opt.rangeY1, opt.rangeY2};
    RectArea area(range, 2);

    //stopcriterion
    Abs stop1;
    StopCriterion * stop;
    stop = &stop1;
    stop ->SetN(opt.maxIter);

    //method
    OptMethod * method;
    GradDesc grad1;
    Stochastic stoc1;
    switch(opt.method){
        case 0:{

            method = &grad1;
            switch(opt.stop_grad_method){
                case 0:
                    stop->SetStopChoice('g');
                    stop->SetEps(opt.eps_grad);
                    break;
                case 1:
                    stop->SetStopChoice('x');
                    stop->SetEps(opt.eps_diff);
                    break;
            }
            break;
        }
        case 1:{

            method = &stoc1;
            switch(opt.stop_stoc_method){
                case 0:
                    stop->SetStopChoice('i');
                    stop->SetMaxItersAfterLast(opt.maxIterAfterLastSuccess);
                    stop->SetEps(opt.eps_diff);
                    break;
                case 1:
                    stop->SetStopChoice('l');
                    method->SetLocalProb(opt.local_prob);
                    break;
            }
            break;
        }
    }

    method -> SetDim(opt.dim);
    method -> SetX0(opt.x_0);
    stop -> SetDim(opt.dim);

    //OPTIMIZE
    opt.min = method -> optimize(&area, f, stop);

    opt.argmin[0] = method -> getXFin()[0];
    opt.argmin[1] = method -> getXFin()[1];
    opt.noOfIterations = method -> GetnIter();

    //PLOT
    QVector<double> xGraph = QVector<double>(method->xGraph.begin(), method->xGraph.end());
    QVector<double> yGraph = QVector<double>(method->yGraph.begin(), method->yGraph.end());
    xGraph.push_front(opt.x_0[0]);
    yGraph.push_front(opt.x_0[1]);

    QCPCurve *pathGraph = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
    //QCPCurve *pathGraph = ui->plot->addGraph();
    pathGraph->setData(xGraph, yGraph);
    pathGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red, 0), QBrush(Qt::red), 5));
    pathGraph->setPen(QPen(Qt::gray, 2));
    QCPCurve *finalPoint = new QCPCurve(ui->plot->xAxis, ui->plot->yAxis);
    QVector<double> argx, argy;
    argx.push_back(opt.argmin[0]);
    argy.push_back(opt.argmin[1]);
    finalPoint->setData(argx, argy);
    finalPoint->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, QPen(Qt::yellow, 3), QBrush(Qt::yellow), 12));
    finalPoint->setPen(QPen(QColor(120, 120, 120), 2));

    ui->plot->replot();

    ui->textBrowser->insertPlainText("min: ");
    QString num;
    num = QString::number(double(opt.min));
    ui->textBrowser->insertPlainText(num);

    ui->textBrowser->insertPlainText("\nargmin: (");
    num = QString::number(double(opt.argmin[0]));
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(";");
    num = QString::number(double(opt.argmin[1]));
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(")");
    ui->textBrowser->insertPlainText("\nIterations:");
    num = QString::number(double(opt.noOfIterations));
    ui->textBrowser->insertPlainText(num);

    ui->plot->QCustomPlot::removePlottable(pathGraph);
    ui->plot->QCustomPlot::removePlottable(finalPoint);
}


void MainWindow::mousePos(QMouseEvent* event)
{

}

void MainWindow::mouseClick(QMouseEvent* event)
{
    ui->textBrowser->insertPlainText("M:");
    QString num;
    ui->plot->mouseMove(event);
    geomx = opt.rangeX1 + (opt.rangeX2-opt.rangeX1)*(double((event->x()) - 57.)/413);
    geomy = opt.rangeY1 + (opt.rangeY2-opt.rangeY1)*(1 - double((event->y()) - 16.)/503);
    //(ui->plot->geometry().x()-57.-80.)
    //(ui->plot->geometry().y()-16.-40.)
    num = QString::number(geomx);
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText(" ");
    num = QString::number(geomy);
    ui->textBrowser->insertPlainText(num);
    ui->textBrowser->insertPlainText("\n");

    ui->x_0->setValue(geomx);
    ui->y_0->setValue(geomy);

    opt.x_0[0] = ui->x_0->value();
    opt.x_0[1] = ui->y_0->value();

    MainWindow::on_pushButton_clicked();

}
