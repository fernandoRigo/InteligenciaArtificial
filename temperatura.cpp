#include "temperatura.h"

temperatura::temperatura(QWidget *parent) :
    QFrame(parent)
{
    this->setFixedHeight(250);
    this->setFixedWidth(700);
    this->setFrameStyle(QFrame::Box);
    this->setWindowTitle("Leitura Da Temperatura");

    this->lVLayout              = new QVBoxLayout();
    this->lHLayout              = new QHBoxLayout();
    this->customPlot            = new QCustomPlot();
    this->lbSesorAtual          = new QLabel();
    this->edSensorAtual         = new QLCDNumber();


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

void temperatura::atualizaGrafico(double y, double x) {


    if(y > maiorTemperatura)
        maiorTemperatura = y;

    if(yAxis.isEmpty())
        yAxis << x;
    else
        yAxis << (x+(yAxis.last()));
    xAxis << y;

    customPlot->graph(0)->setData(yAxis,xAxis);
    customPlot->yAxis->setLabel("Temperatura");
    customPlot->yAxis->setRange(0, maiorTemperatura);
    customPlot->xAxis->setRange(0,yAxis.last());
    customPlot->xAxis->setLabel("Tempo (s)");
    customPlot->replot();
}


temperatura::~temperatura() {
    yAxis.clear();
    xAxis.clear();
}
