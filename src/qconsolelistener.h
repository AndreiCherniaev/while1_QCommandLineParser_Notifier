#pragma once

#include <QObject>
#include <QSocketNotifier>

class QConsoleListener : public QObject
{
    Q_OBJECT
public:
    explicit QConsoleListener(QObject *parent = nullptr);
signals:
    void finishedGetLine(const QString message);
public slots:
    void text(QSocketDescriptor d, QSocketNotifier::Type t);
private:
    QSocketNotifier *m_notifier;
};
