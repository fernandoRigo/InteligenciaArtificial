#include "Tela.h"

Tela::Tela() {
    QIcon icone;
    icone.addFile(":/new/img/System Profiler.png");
    this->setWindowIcon(icone);
    this->setWindowTitle("Porta Serial");
    this->setFixedWidth(200);

    portasDisponiveis = new QComboBox();
    lbDescricao       = new QLabel("Selecione A Porta Serial:");
    portas            = new Serial();
    principal         = new QVBoxLayout();
    fechaTela         = new QTimer();

    QList <QString> dialog = portas->listaPortas();
    dialog.push_back("");

    for(int i = dialog.size() -1 ; i >= 0 ; i--) {
        portasDisponiveis->addItem(dialog.at(i));
    }

    principal->addWidget(lbDescricao);
    principal->addWidget(portasDisponiveis);
    this->setLayout(principal);

    fechaTela->start(100);
    connect(portasDisponiveis,SIGNAL(currentIndexChanged(int)),this,SLOT(selecionaPorta(int)));
    connect(fechaTela,SIGNAL(timeout()),this,SLOT(fecharTela()));
}

Tela::~Tela() {

}

void Tela::selecionaPorta(int a){
    portas->selecionaPorta(a);
}

void Tela::fecharTela() {
    if(portas->getTela())
        this->close();
}

