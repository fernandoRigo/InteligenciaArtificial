#pragma once
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QLCDNumber>
#include <QFrame>
#include <QTimer>
#include "qcustomplot.h"
class potencia : public QFrame
{
    Q_OBJECT
public:
    potencia(QWidget *parent = 0);
    ~potencia();
    QCustomPlot *customPlot;
    QLabel * lbSesorAtual;
    QLCDNumber * edSensorAtual;
    QTimer * timerAtualizaSensores;

    QVBoxLayout *lVLayout;
    QHBoxLayout *lHLayout;
    QVector <double> xAxis;
    QVector <double> yAxis;
    //FormPrincipal form;
private:
    double maiorPotencia;

signals:

public slots:
    void atualizaGrafico(double x, double y,char c);
};
