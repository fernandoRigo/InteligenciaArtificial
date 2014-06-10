#pragma once
#include "temperatura.h"
#include "potencia.h"
#include "tensao.h"
#include "rotacao.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QMainWindow>
#include <QImage>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class FormPrincipal :public QMainWindow
{
    Q_OBJECT
    public:
    FormPrincipal(QSerialPortInfo port);
    ~FormPrincipal();

    QSerialPort portaSelecionada;
    QImage * image;
    temperatura *formTemperatura;
    potencia *formPotencia;
    tensao *formTensao;
    rotacao *formRotacao;
    float rtTemperatura;
    float rtPotencia;
    float rtTensao;
    float rtRotacao;
    float rtCorrente;

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    QTimer * atualizaSensores;
    QTimer * atualizaTela;

signals:
    void atualizaTemperatura(double x, double y, char c);
    void atualizaPotencia(double x, double y, char c);
    void atualizaCorrente(double x, double y, char c);
    void atualizaRotacao(double x, double y, char c);
    void atualizaTensao(double x, double y, char c);

public slots:
    void leDados();
};
