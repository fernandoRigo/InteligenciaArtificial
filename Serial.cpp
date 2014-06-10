#include "Serial.h"
#include <iostream>

Serial::Serial() {
    mostraTela = false;
}

Serial::~Serial() {

}

QList<QString> Serial::listaPortas() {
    int i = 0;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QString dialogStr = info.portName();
        listaDePortasSeriais.insert(i,info);
        listaDePortas.insert(i,dialogStr);
        i++;
    }
    return listaDePortas;
}

void Serial::selecionaPorta(int porta) {
    portaSelecionada.setPort(listaDePortasSeriais.at(porta));
    portaSelecionada.setBaudRate(QSerialPort::Baud38400);
    portaSelecionada.setDataBits(QSerialPort::Data8);
    portaSelecionada.setParity(QSerialPort::NoParity);
    portaSelecionada.setStopBits(QSerialPort::OneStop);
    if (portaSelecionada.open(QIODevice::ReadWrite)) {
        portaSelecionada.close();
        principal = new FormPrincipal(listaDePortasSeriais.at(porta));
        mostraTela = true;
        principal->show();
    }
}

bool Serial::getTela() {
    return mostraTela;
}

