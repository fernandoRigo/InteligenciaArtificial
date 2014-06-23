#include <QtWidgets>
#include <QLabel>
#include <QHBoxLayout>

class Erro : public QWidget {
public:
    Erro();
    ~Erro();
    void setMensagem(QString mensagem);
private:
    QLabel * msgErro;
    QHBoxLayout * layoutPrincipal;
};
