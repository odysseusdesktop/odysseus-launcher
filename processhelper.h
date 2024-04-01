#ifndef PROCESSHELPER_H
#define PROCESSHELPER_H

#include <QObject>
#include <QProcess>
#include <QRegularExpression>

class ProcessHelper : public QObject
{
    Q_OBJECT
public:
    explicit ProcessHelper(QObject *parent = nullptr);
public slots:
    void start(QString programName);
signals:

};

#endif // PROCESSHELPER_H
