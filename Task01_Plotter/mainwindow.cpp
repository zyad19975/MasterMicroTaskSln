#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "parser.h"
#include <bits/stdc++.h>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot(){
    string expstr = ui->textEdit->toPlainText().toStdString();
    parser ob;
    int minx = ui->horizontalSlider->value();
    int maxx = ui->horizontalSlider_2->value();
    // generate some data:
    int miny = 100000;
    int maxy = -1000000;
    int size = (maxx - minx)*10;
    QVector<double> x(size+1), y(size+1); // initialize with entries 0..100
    int index=0;
    for (double j = minx; j < maxx; j+=0.1){
        char finalExp[50];
        string s = expstr;
        for (int i = 0; i < s.length(); i++){
            if(s[i] == 'x'){
                s.replace(i, 1,to_string(j));
            }
        }
        strcpy(finalExp, s.c_str());
        double ans;
        try
        {
            ans =ob.eval_exp(finalExp);
            string err(ob.errormsg);
            if(!err.empty()){
                throw err;
            }

        }catch (string err)
        {
            QMessageBox msgBox;
            msgBox.setText("Error");
            msgBox.setInformativeText(QString::fromStdString(err));
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.exec();
            return;
        }

        if(ans > maxy){
            maxy = (int) ans;
        }
        if(ans < miny){
            miny= (int) ans;
        }
         x[index] = j;
         y[index] = ans;
         index++;

    }



    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(minx, maxx);
    ui->customPlot->yAxis->setRange(miny, maxy);
    ui->customPlot->replot();
}

void MainWindow::on_pushButton_clicked()
{
       MainWindow::makePlot();
}

void MainWindow::on_textEdit_textChanged()
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{

    ui->min_label->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    ui->max_label->setText(QString::number(value));
}
