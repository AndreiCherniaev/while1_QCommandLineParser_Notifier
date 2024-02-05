//https://stackoverflow.com/questions/6878507/using-qsocketnotifier-to-select-on-a-char-device/7389622#7389622
#include "qconsolelistener.h"
//#include <QTextStream> //for QTextStream way only
#include <iostream>
#include <unistd.h> //Provides STDIN_FILENO

QConsoleListener::QConsoleListener(QObject *parent) :
    QObject(parent),
    m_notifier(new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this))
{
    connect(m_notifier, &QSocketNotifier::activated, this, &QConsoleListener::text);
}

void QConsoleListener::text(QSocketDescriptor d, QSocketNotifier::Type t)
{
    /*//QTextStream way
    QTextStream qin(stdin);
    QString line = qin.readLine();
    emit textReceived(line);*/

    //main way
//https://stackoverflow.com/questions/6878507/using-qsocketnotifier-to-select-on-a-char-device/7389622#comment71257508_7389622
    std::string line;
    std::getline(std::cin, line);
    emit finishedGetLine(QString::fromStdString(line));
}
