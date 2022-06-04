TEMPLATE = app
CONFIG += console c++19
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bullet.cpp \
        button.cpp \
        main.cpp \
        normalshot.cpp \
        player.cpp

INCLUDEPATH += "C:/SFML-2.5.1/include"

LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

HEADERS += \
    bullet.h \
    button.h \
    normalshot.h \
    player.h
