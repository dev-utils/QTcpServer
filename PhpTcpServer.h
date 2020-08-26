#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class PhpTcpServer : public QObject
{
    Q_OBJECT
public:
    PhpTcpServer(unsigned short port, QObject *parent=0);
    ~PhpTcpServer();

private slots:
    void onNewConnection();

    void onAcceptError(QAbstractSocket::SocketError socketError);
    void onReadyRead();

private:
    QTcpServer *m_pTcpServer = nullptr;
};

#endif // TCPSERVER_H
