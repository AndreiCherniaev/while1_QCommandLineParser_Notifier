//https://stackoverflow.com/questions/6878507/using-qsocketnotifier-to-select-on-a-char-device/7389622#7389622
#include "ConsoleReader.h"
#include <QTextStream>

#include <unistd.h> //Provides STDIN_FILENO

ConsoleReader::ConsoleReader(QObject *parent) :
    QObject(parent),
    notifier(new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read, this))
{
    connect(notifier, SIGNAL(activated(int)), this, SLOT(text()));
}

void ConsoleReader::text()
{
    QTextStream qin(stdin);
    QString line = qin.readLine();
    emit textReceived(line);
}
