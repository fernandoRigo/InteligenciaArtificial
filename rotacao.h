#pragma once
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QLCDNumber>
#include <QFrame>
#include <QTimer>
#include <QPushButton>
#include "qcustomplot.h"
class rotacao : public QFrame
{
    Q_OBJECT
public:
    rotacao(QWidget *parent = 0);
    ~rotacao();
    QCustomPlot *customPlot;
    QLabel * lbSesorAtual;
    QLCDNumber * edSensorAtual;
    QTimer * timerAtualizaSensores;
    QPushButton *btLimpar;
    QVBoxLayout *lVLayout;
    QHBoxLayout *lHLayout;
    QVector <double> xAxis;
    QVector <double> yAxis;
    //FormPrincipal form;

private:
    double maiorRotacao;

signals:

public slots:
    void atualizaGrafico(double y,double x);
    void atualizaSensor(char c);
    void limpaGrafico();
};
