#include <QApplication>
#include <QtCore/QDebug>
#include "Tela.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Example use QSerialPortInfo

   Tela *tela = new Tela();
    tela->show();

    return a.exec();
}
