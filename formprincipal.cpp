#include "formprincipal.h"
#include <QPainter>
#include <iostream>

FormPrincipal::FormPrincipal(QSerialPortInfo port)

{
    QString filename = ":/new/img/usina-eolica-turbina-eolica-energia-eolica_yubqha.jpg";

    this->image = new QImage(filename);
    this->formTemperatura = new temperatura();
    this->formPotencia = new potencia();
    this->formRotacao = new rotacao();
    this->formTensao = new tensao();

    this->setFixedHeight(image->height());
    this->setFixedWidth(image->width());

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
    connect(atualizaSensores,SIGNAL(timeout()),this,SLOT(leDados()));
    update();
}

FormPrincipal ::~FormPrincipal(){

}

void FormPrincipal::paintEvent(QPaintEvent *e){
    QPainter painter(this);

    painter.drawImage(QPoint(0,0), *image);
    painter.setPen(Qt::green); //Rotação
    painter.drawRect(425,265,10,20);
    painter.setPen(Qt::yellow); //Potencia
    painter.drawRect(265,275,10,20);
    painter.setPen(Qt::red); //Temperatura
    painter.drawRect(345,270,10,20);
    painter.setPen(Qt::white); //Tensão
    painter.drawRect(320,330,10,20);

    //VALORES EM TEMPO REAL
    painter.setPen(Qt::lightGray);
    painter.drawRect(10,15,240,100);

    QString s = "Valores Em Tempo Real";
    QString x;
    painter.drawText(15,10,s);
    painter.setPen(Qt::green); //Rotação
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
    painter.setPen(Qt::lightGray);
    painter.drawText(10,400,s);

    painter.setPen(Qt::green); //Rotação
    painter.drawRect(10,405,10,20);
    s = "Rotação Do Motor";
    painter.drawText(25,417,s);

    painter.setPen(Qt::white); //Tensão
    painter.drawRect(10,427,10,20);
    s = "Potência Do Motor";
    painter.drawText(25,439,s);

    painter.setPen(Qt::red); //Temperatura
    painter.drawRect(10,450,10,20);
    s = "Temperatura Da Turbina";
    painter.drawText(25,462,s);

    painter.setPen(Qt::yellow); //Potencia
    painter.drawRect(10,473,10,20);
    s = "Tensão Do Circuito";
    painter.drawText(25,485,s);
}

bool ehTemperatura(int x, int y){
    if ((x >= 345 && x <=375)
            && (y >= 270&& y <= 280)) {
        return true;
    } else {
        return false;
    }
}

bool ehTensao(int x, int y){
    if ((x >= 265 && x <=285)
            && (y >= 275&& y <= 295)) {
        return true;
    } else {
        return false;
    }
}

bool ehPotencia(int x, int y){
    if ((x >= 320 && x <=340)
            && (y >= 330&& y <= 350)) {
        return true;
    } else {
        return false;
    }
}

bool ehRotacao(int x, int y){
    if ((x >= 425 && x <=445)
            && (y >= 265&& y <= 285)) {
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

void FormPrincipal::leDados(){
    QByteArray dados = portaSelecionada.readAll();
    unsigned char low;
    unsigned char high;
    int16_t valor;
    char sensorAtual;
    int posPotencia     = 0;
    int posTemperatura  = 0;
    int posRPM          = 0;

//    INT16 testa = 15;


//    char low1 = (char)testa;
//    char high1 = testa >> 8;

//    dados[0] =  '[';
//    dados[1] =  'T';
//    dados[2] =  'A';
//    dados[3] =  ',';
//    dados[4] =  low1;
//    dados[5] =  high1;
//    dados[6] =  ']';


    posPotencia     = dados.indexOf('P');
    posTemperatura  = dados.indexOf('T');
    posRPM          = dados.indexOf('R');

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
        this->rtCorrente = ((this->rtCorrente/12.5)*1000);

        emit atualizaCorrente(this->rtCorrente,1.0);

        //POTENCIA
        this->rtPotencia = this->rtTensao * this->rtCorrente;

        emit atualizaPotencia(this->rtPotencia ,1.0);
    }

    //TEMPERATURA
    if (posTemperatura != -1){
        // [XA,LH][XA,LH][XA,LHLH]
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
    }
    update();
}



