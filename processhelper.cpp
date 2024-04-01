#include "processhelper.h"
// TODO: REMOVE
#include <QDebug>

ProcessHelper::ProcessHelper(QObject *parent)
    : QObject{parent}
{

}

void ProcessHelper::start(QString programName)
{
    QRegularExpression re("\\s+"); // Regular expression to split by spaces
    QStringList parts = programName.split(re);

    QStringList arguments;
    QString executable;

    bool insideQuotes = false;
    QString currentArg;


    // this is hot garbage
    for (const QString &part : parts) {
        if (!insideQuotes) {
            // If we're not inside quotes, check if the part starts with a quote
            if (part.startsWith("'")) {
                // If so, this is the start of quoted text
                insideQuotes = true;
                // Remove the opening quote from the part
                currentArg = part.mid(1);
            } else {
                // If not, it's a normal argument
                arguments.append(part);
            }
        } else {
            // If we're inside quotes, check if this part ends with a quote
            if (part.endsWith("'")) {
                // If so, this is the end of quoted text
                insideQuotes = false;
                // Append the part (without the closing quote) to the current argument
                currentArg += " " + part.left(part.length() - 1);
                // Add the fully formed argument to the list
                arguments.append(currentArg);
            } else {
                // If not, just append the part to the current argument
                currentArg += " " + part;
            }
        }
    }

    // remove %u %U %f %F
    QStringList invalid = {"%u", "%U", "%f", "%F"};
    for(const QString arg : arguments) {
        if(invalid.contains(arg)) arguments.removeOne(arg);
    }

    executable = arguments.takeFirst();
    qDebug() << "Executable:" << executable;
    qDebug() << "Arguments:" << arguments;

    QProcess::startDetached(executable, arguments);
}
