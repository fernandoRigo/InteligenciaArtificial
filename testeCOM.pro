QT += serialport widgets printsupport

HEADERS += \
    qcustomplot.h \
    temperatura.h \
    formprincipal.h \
    potencia.h \
    tensao.h \
    rotacao.h \
    Serial.h \
    Tela.h \
    Erro.h

SOURCES += \
    main.cpp \
    formprincipal.cpp \
    qcustomplot.cpp \
    temperatura.cpp \
    potencia.cpp \
    tensao.cpp \
    rotacao.cpp \
    Serial.cpp \
    Tela.cpp \
    Erro.cpp

RESOURCES += \
    Imagens.qrc



CONFIG += serialport
