#include <QCoreApplication>
#include "PhpTcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    PhpTcpServer tcpServer(18001);
    return a.exec();
}
