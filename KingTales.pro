QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ammo.cpp \
    Book.cpp \
    Consumable.cpp \
    Button.cpp \
    FireBall.cpp \
    Game.cpp \
    Goblin.cpp \
    Ground.cpp \
    Health.cpp \
    Hole.cpp \
    Monster.cpp \
    Platform.cpp \
    Player.cpp \
    Potion.cpp \
    RectPlatform.cpp \
    Scene.cpp \
    main.cpp

HEADERS += \
    Ammo.h \
    Book.h \
    Consumable.h \
    Button.h \
    FireBall.h \
    Game.h \
    Goblin.h \
    Ground.h \
    Health.h \
    Hole.h \
    Monster.h \
    Platform.h \
    Player.h \
    Potion.h \
    RectPlatform.h \
    Scene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
