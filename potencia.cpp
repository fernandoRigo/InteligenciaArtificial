#include "potencia.h"

potencia::potencia(QWidget *parent) :
    QFrame(parent)
{
    this->setFixedHeight(250);
    this->setFixedWidth(700);
    this->setFrameStyle(QFrame::Box);
    this->setWindowTitle("Leitura Da Potência Watts");

    this->lVLayout = new QVBoxLayout();
    this->lHLayout = new QHBoxLayout();
    this->customPlot = new QCustomPlot();

    this->lbSesorAtual = new QLabel();
    this->edSensorAtual = new QLCDNumber();

    this->edSensorAtual->setDigitCount(1);
    this->edSensorAtual->setFixedWidth(30);
    this->edSensorAtual->setFixedHeight(40);
    this->edSensorAtual->setSegmentStyle(QLCDNumber::Flat);

    this->lbSesorAtual->setText("Sensor \nAtual:");
    this->customPlot->addGraph();

    this->lVLayout->addWidget(lbSesorAtual);
    this->lVLayout->addWidget(edSensorAtual);

    this->lHLayout->addLayout(lVLayout);
    this->lHLayout->addWidget(customPlot);

    this->setLayout(lHLayout);

}

void potencia::atualizaGrafico(double x,double y,char c) {
    this->edSensorAtual->display(c);

    if(x > maiorPotencia)
        maiorPotencia = x;

    if(yAxis.isEmpty())
        yAxis << y;
    else
        yAxis << (y+(yAxis.last()));
    xAxis << x;



    customPlot->graph(0)->setData(xAxis, yAxis);
    customPlot->yAxis->setLabel("Potência");
    customPlot->yAxis->setRange(0, maiorPotencia);
    customPlot->xAxis->setRange(0,yAxis.last());
    customPlot->xAxis->setLabel("Tempo (s)");
    customPlot->replot();
}


potencia::~potencia(){
    xAxis.clear();
    yAxis.clear();
}
