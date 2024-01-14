#pragma once

#include <QObject>
#include <QSocketNotifier>

class ConsoleReader : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleReader(QObject *parent = nullptr);
signals:
    void textReceived(const QString message);
public slots:
    void text(QSocketDescriptor d, QSocketNotifier::Type t);
private:
    QSocketNotifier *notifier;
};
