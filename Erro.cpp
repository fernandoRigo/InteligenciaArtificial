#include "Erro.h"

Erro::Erro() {
    msgErro = new QLabel();
    layoutPrincipal = new QHBoxLayout();
    layoutPrincipal->addWidget(msgErro);
    this->setLayout(layoutPrincipal);
}
Erro::~Erro() {
    delete msgErro;
}
void Erro::setMensagem(QString mensagem) {
    msgErro->setText(mensagem);
}
