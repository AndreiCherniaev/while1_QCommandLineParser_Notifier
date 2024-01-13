#pragma once

#include <QTimer>
#include <QThread>
#include "Worker.h"

class MainClass : public QObject
{
    Q_OBJECT

    QTimer timer;
public:    
    explicit MainClass(QObject *parent = 0);
    ~MainClass();

private slots:
    void handleSignal();
    void mycallback(QStringView message);

public slots:
    void threadIsFinished();

private:
    QScopedPointer<Worker> worker;  //наш объект, в методах которого мы можем писать пользовательские алгоритмы обращаясь по необходимости ко всему богатству Qt
    QScopedPointer<QThread> thread; //наша дополнительная нить, ради которой весь сыр-бор
};
