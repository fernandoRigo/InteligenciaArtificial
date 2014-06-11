#pragma once
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QLCDNumber>
#include <QTimer>
#include "qcustomplot.h"
class temperatura : public QFrame
{
    Q_OBJECT
public:
    temperatura(QWidget *parent = 0);
    ~temperatura();
    QCustomPlot *customPlot;
    QLabel * lbSesorAtual;
    QLCDNumber * edSensorAtual;
    QTimer * timerAtualizaSensores;

    QVBoxLayout *lVLayout;
    QHBoxLayout *lHLayout;
    QVector <double> xAxis;
    QVector <double> yAxis;

private:
    double maiorTemperatura;

signals:
    
public slots:
    void atualizaGrafico(double y, double x);
};

