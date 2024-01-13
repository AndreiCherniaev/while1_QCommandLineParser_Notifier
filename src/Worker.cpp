#include "Worker.h"
#include "qthread.h"
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent),
    m_message("")
{
    qDebug() << "Worker::Worker";
    connect(&reader, &ConsoleReader::textReceived, this, &Worker::textReceivedCallback);
    /*
    By the way, one extremely important thing to note here is that you should NEVER allocate heap objects (using new) in the
    constructor of the QObject class as this allocation is then performed on the main thread and not on the new QThread instance,
    meaning that the newly created object is then owned by the main thread and not the QThread instance. This will make your code
    fail to work. Instead, allocate such resources in the main function slot such as process() in this case as when that is called
    the object will be on the new thread instance and thus it will own the resource. https://wiki.qt.io/QThreads_general_usage
    */
}


QString Worker::message() const
{
    return m_message;
}


void Worker::textReceivedCallback(const QString message){
    QStringList cmd = QCoreApplication::arguments()<< message.split(" ");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("command", "The command to execute." );

    parser.parse(cmd);
    const QStringList args = parser.positionalArguments();
    const QString command = args.isEmpty() ? QString() : args.first();
    if(command == "c"){
        qDebug() << "!c!" << m_message << count;
    }
}


//Самый важный метод, в котором будет выполняться "полезная" работа объекта
void Worker::run()
{
    count = 0;
    while(1)
    {
        QCoreApplication::processEvents();
        if (QThread::currentThread()->isInterruptionRequested()){
            goto exit_LABEL;
        }
        //If noCheck==true then no way to send wrong CMD,
        //else user can send CMD with wrong values
        bool noCheck= false;
        bool cmd_correct= true;
       /*QTextStream(stdout)<< "# ";
        QTextStream qin(stdin);*/

        count++;
        emit sendMessage(m_message); //высылаем данные, которые будут передаваться в другой поток
        QThread::sleep(1); //1 s pause
    }
exit_LABEL:;
    emit finished();
    qDebug() << "emit finished()";
}


void Worker::setMessage(QString message)
{
    if (m_message == message)
        return;

    m_message = message;
    emit messageChanged(message);
}


Worker::~Worker()
{
    qDebug() << "~Worker()";
}
