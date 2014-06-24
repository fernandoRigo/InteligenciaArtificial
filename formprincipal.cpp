#include "formprincipal.h"
#include <QPainter>
#include <iostream>

FormPrincipal::FormPrincipal(QSerialPortInfo port)

{

    QString filename = ":/new/img/0_gerador_eolico_detalhe_alternador.png";

    this->image = new QImage(filename);
    this->formTemperatura = new temperatura();
    this->formPotencia = new potencia();
    this->formRotacao = new rotacao();
    this->formTensao = new tensao();
    this->mensagem = new Erro();
    this->setWindowState(Qt::WindowMaximized);
    this->setMinimumSize(image->width(),image->height());

    this->rtPotencia    = 0;
    this->rtRotacao     = 0;
    this->rtTemperatura = 0;
    this->rtTensao      = 0;

    this->atualizaSensores = new QTimer();
    atualizaSensores->start(100);
    this->atualizaTela = new QTimer();
    qDebug()<<port.portName();
    portaSelecionada.setPortName(port.portName());
    if(portaSelecionada.open(QIODevice::ReadWrite) ) {
        bool sucess = portaSelecionada.setBaudRate(QSerialPort::Baud38400) &
                portaSelecionada.setStopBits(QSerialPort::OneStop) &
                portaSelecionada.setDataBits(QSerialPort::Data8) &
                portaSelecionada.setParity(QSerialPort::NoParity) &
                portaSelecionada.setFlowControl(QSerialPort::NoFlowControl);
        qDebug() << sucess;
    } else {
        qDebug() << "Falha ao abrir a porta";
    }

    connect(this,SIGNAL(atualizaTemperatura(double,double)),formTemperatura,SLOT(atualizaGrafico(double,double)));
    connect(this,SIGNAL(atualizaTensao(double,double)),formTensao,SLOT(atualizaGrafico(double,double)));
    connect(this,SIGNAL(atualizaRotacao(double,double)),formRotacao,SLOT(atualizaGrafico(double,double)));
    connect(this,SIGNAL(atualizaPotencia(double,double)),formPotencia,SLOT(atualizaGrafico(double,double)));
    connect(this,SIGNAL(atualizaSensor(char)),formTemperatura,SLOT(atualizaSensor(char)));
    connect(this,SIGNAL(atualizaSensor(char)),formRotacao,SLOT(atualizaSensor(char)));

    connect(atualizaSensores,SIGNAL(timeout()),this,SLOT(leDados()));
    update();
}

FormPrincipal ::~FormPrincipal(){

}

void FormPrincipal::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    painter.drawImage(QPoint(0,0), *image);
    painter.setPen(Qt::green); //Rotação
    painter.drawRect(768,380,10,20);
    painter.setPen(Qt::white); //Potencia
    painter.drawRect(700,380,10,20);
    painter.setPen(Qt::red); //Temperatura
    painter.drawRect(640,380,10,20);
    painter.setPen(Qt::yellow); //Tensão
    painter.drawRect(85,340,10,20);

    //VALORES EM TEMPO REAL
    painter.setPen(Qt::black);
    painter.drawRect(10,15,240,100);

    QString s = "Valores Em Tempo Real";
    QString x;
    painter.drawText(15,10,s);
    painter.setPen(Qt::darkGreen); //Rotação
    x.setNum(rtRotacao);
    s = "Rotação da turbina: ";
    s.append(x);
    painter.drawText(15,30,s);

    painter.setPen(Qt::yellow); //Tensão
    x.setNum(rtTensao, 'f', 2);
    s = "Tensão do Motor: ";
    s.append(x);
    painter.drawText(15,50,s);

    painter.setPen(Qt::red); //Temperatura
    x.setNum(rtTemperatura, 'f', 2);
    s = "Temperatura da turbina: ";
    s.append(x);
    painter.drawText(15,70,s);

    painter.setPen(Qt::white); //Potencia
    x.setNum(rtPotencia, 'f', 2);
    s = "Potência do Motor: ";
    s.append(x);
    painter.drawText(15,90,s);


    //LEGENDA
    s = "Legenda";
    painter.setPen(Qt::black);
    painter.drawText(10,600,s);

    painter.setPen(Qt::darkGreen); //Rotação
    painter.drawRect(10,605,10,20);
    s = "Rotação Do Motor";
    painter.drawText(25,617,s);

    painter.setPen(Qt::white); //Tensão
    painter.drawRect(10,627,10,20);
    s = "Potência Do Motor";
    painter.drawText(25,639,s);

    painter.setPen(Qt::red); //Temperatura
    painter.drawRect(10,650,10,20);
    s = "Temperatura Da Turbina";
    painter.drawText(25,662,s);

    painter.setPen(Qt::yellow); //Potencia
    painter.drawRect(10,673,10,20);
    s = "Tensão Do Circuito";
    painter.drawText(25,685,s);

    //Mensagem
    painter.setPen(Qt::red);
    QFont *fonteGradona = new QFont(QString("Courier"), -1, 14,false);
    fonteGradona->setPixelSize(20);
    painter.setFont(*fonteGradona);
    if(!lbMensagem.isEmpty()){
        painter.drawText(290,20,lbMensagem.first());
    }

}

bool ehTemperatura(int x, int y){
    if ((x >= 640 && x <=650)
            && (y >= 380&& y <= 410)) {
        return true;
    } else {
        return false;
    }
}

bool ehTensao(int x, int y){
    if ((x >= 85 && x <=95)
            && (y >= 340&& y <= 360)) {
        return true;
    } else {
        return false;
    }
}

bool ehPotencia(int x, int y){
    if ((x >= 700 && x <=710)
            && (y >= 380&& y <= 400)) {
        return true;
    } else {
        return false;
    }
}

bool ehRotacao(int x, int y){
    if ((x >= 768 && x <=778)
            && (y >= 380&& y <= 400)) {
        return true;
    } else {
        return false;
    }
}

void FormPrincipal::mousePressEvent(QMouseEvent *e){
    QMainWindow::mousePressEvent(e);

    int x = e->localPos().x();
    int y = e->localPos().y();

    if(ehTemperatura(x,y)){
        formTemperatura->show();
    }else if(ehPotencia(x,y)){
        formPotencia->show();
    }else if(ehRotacao(x,y)){
        formRotacao->show();
    }else if(ehTensao(x,y)){
        formTensao->show();
    }
}

void FormPrincipal::limpaMensagem(){
    listTimer.first()->~QTimer();
    listTimer.removeFirst();
    lbMensagem.removeFirst();

}

void FormPrincipal::leDados(){
    QByteArray dados = portaSelecionada.readAll();
    unsigned char low;
    unsigned char high;
    int16_t valor;
    char sensorAtual;
    int posPotencia     = 0;
    int posTemperatura  = 0;
    int posRPM          = 0;

    posPotencia     = dados.indexOf('P');
    posTemperatura  = dados.indexOf('T');
    posRPM          = dados.indexOf('R');

    //MENSAGEM
    if (dados.startsWith("[m,")) {
        //Mostrar mensagem
        QString dialog;
        QTimer *timerAux = new QTimer();
        int i = 3;
        while (dados.at(i) != ']') {
            dialog.insert((i-3),dados.at(i));
            i++;
        }
        connect(timerAux, SIGNAL(timeout()),this,SLOT(limpaMensagem()));

        timerAux->start(5000);
        listTimer.push_back(timerAux);
        lbMensagem.push_back(dialog);
    }

    //POTENCIA, TENSAO, CORRENTE
    if (posPotencia != -1){
        //TENSAO
        if (dados[posPotencia + 3] =='#') {
            low  = 0x00;
        } else {
            low  = dados[posPotencia + 3];
        }

        if (dados[posPotencia + 4] =='#') {
            high = 0x00;
        } else {
            high = dados[posPotencia + 4];
        }
        sensorAtual = dados[posPotencia+1];

        valor = (high<<8) | low;
        this->rtTensao = valor*(5.0/1023.0)*2.0;

        emit atualizaTensao(this->rtTensao,1.0);

        //CORRENTE
        if (dados[posPotencia + 5] =='#') {
            low  = 0x00;
        } else {
            low  = dados[posPotencia + 5];
        }

        if (dados[posPotencia + 6] =='#') {
            high = 0x00;
        } else {
            high = dados[posPotencia + 6];
        }

        valor = (high<<8) | low;


        this->rtCorrente = valor*(5.0/1023.0);
        this->rtCorrente = this->rtCorrente/10.0;
        this->rtCorrente = ((this->rtCorrente/2.5)*1000);

        emit atualizaCorrente(this->rtCorrente,1.0);

        //POTENCIA
        this->rtPotencia = this->rtTensao * this->rtCorrente;

        emit atualizaPotencia(this->rtPotencia ,1.0);
    }

    //TEMPERATURA
    if (posTemperatura != -1){
        // [TA,LH][XA,LH][XA,LHLH]
        if (dados[posTemperatura+3] =='#') {
            low  = 0x00;
        } else {
            low  = dados[posTemperatura+3];
        }

        if (dados[posTemperatura+4] =='#') {
            high = 0x00;
        } else {
            high = dados[posTemperatura+4];
        }
        valor = (high<<8) | low;
        this->rtTemperatura = (5.0 * valor * 100.0 / 1023.0);
        sensorAtual = dados[posTemperatura+1];

        emit atualizaTemperatura(rtTemperatura,1.0);

        //Sensor Atual
        emit atualizaSensor(dados[posTemperatura+1]);
    }

    //RPM
    if (posRPM != -1){
        // [XA,LH][XA,LH][XA,LHLH]
        if (dados[posRPM+3] =='#') {
            low  = 0x00;
        } else {
            low  = dados[posRPM+3];
        }

        if (dados[posRPM+4] =='#') {
            high = 0x00;
        } else {
            high = dados[posRPM+4];
        }

        float rpmTemp = (high<<8) | low;;

        if (rpmTemp >= 0 && rpmTemp < 1500) {
            this->rtRotacao = rpmTemp;
        }
        sensorAtual = dados[posRPM+1];

        emit atualizaRotacao(rtRotacao,1.0);

        //Sensor Atual
        emit atualizaSensor(dados[posRPM+1]);

    }
    update();
}



