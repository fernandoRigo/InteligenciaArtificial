#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QObject>
#include <QList>
#include <QTimer>
#include "Serial.h"
class Tela : public QWidget {

    Q_OBJECT

private:
    QComboBox * portasDisponiveis;
    Serial * portas;
    QHBoxLayout * principal;
    QTimer * fechaTela;

public:
    Tela();
    ~Tela();

public slots:
    void selecionaPorta(int a);
    void fecharTela();
};
