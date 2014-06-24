#include "potencia.h"

potencia::potencia(QWidget *parent) :
    QFrame(parent)
{
    this->setFixedHeight(250);
    this->setFixedWidth(700);
    this->setFrameStyle(QFrame::Box);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setWindowTitle("Leitura Da Potência em Watts");

    this->lVLayout      = new QVBoxLayout();
    this->lHLayout      = new QHBoxLayout();
    this->customPlot    = new QCustomPlot();
    this->btLimpar      = new QPushButton();
    this->lbSesorAtual  = new QLabel();
    this->edSensorAtual = new QLCDNumber();

    this->edSensorAtual->setDigitCount(1);
    this->edSensorAtual->setFixedWidth(30);
    this->edSensorAtual->setFixedHeight(40);
    this->edSensorAtual->setSegmentStyle(QLCDNumber::Flat);
    this->btLimpar->setText("Limpar");
    this->btLimpar->setMaximumWidth(50);
    this->lbSesorAtual->setText("Sensor \nAtual:");
    this->customPlot->addGraph();

    this->lVLayout->addWidget(lbSesorAtual);
    this->lVLayout->addWidget(edSensorAtual);
    this->lVLayout->addWidget(btLimpar);

    this->lHLayout->addLayout(lVLayout);
    this->lHLayout->addWidget(customPlot);

    this->setLayout(lHLayout);

    connect(btLimpar,SIGNAL(clicked()),this,SLOT(limpaGrafico()));

}

void potencia::limpaGrafico(){
    maiorPotencia = 0;
    customPlot->yAxis->setRange(0,0);
    customPlot->xAxis->setRange(0,0);
    customPlot->graph(0)->clearData();
}

void potencia::atualizaGrafico(double y,double x) {
    //this->edSensorAtual->display(c);

    if(y > maiorPotencia)
        maiorPotencia = y;

    if(yAxis.isEmpty())
        yAxis << x;
    else
        yAxis << (x+(yAxis.last()));
    xAxis << y;



    customPlot->graph(0)->setData(yAxis,xAxis);
    customPlot->yAxis->setLabel("Potencia");
    customPlot->yAxis->setRange(0, maiorPotencia);
    customPlot->xAxis->setRange(0,yAxis.last());
    customPlot->xAxis->setLabel("Tempo (s)");
    customPlot->replot();
}



potencia::~potencia(){
    xAxis.clear();
    yAxis.clear();
}
