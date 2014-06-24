#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QObject>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QPushButton>
#include "Serial.h"
class Tela : public QWidget {

    Q_OBJECT

private:
    QComboBox * portasDisponiveis;
    Serial * portas;
    QVBoxLayout * principal;
    QTimer * fechaTela;
    QLabel * lbDescricao;

public:
    Tela();
    ~Tela();

public slots:
    void selecionaPorta(int a);
    void fecharTela();
};
