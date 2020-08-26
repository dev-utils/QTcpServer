#include "PhpTcpServer.h"
#include <QTcpSocket>

PhpTcpServer::PhpTcpServer(unsigned short port, QObject *parent) :
    QObject(parent)
{
    m_pTcpServer = new QTcpServer();
    connect(m_pTcpServer, &QTcpServer::newConnection, this, &PhpTcpServer::onNewConnection);
    connect(m_pTcpServer, &QTcpServer::acceptError, this, &PhpTcpServer::onAcceptError);
    if (!m_pTcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "m_pTcpServer->listen() error";
        assert(false);
    } else {
        qDebug() <<"start listen:" << port;
    }
}

void PhpTcpServer::onNewConnection() {
    QTcpSocket* pClientConnection = m_pTcpServer->nextPendingConnection();
    if (pClientConnection) {
        connect(pClientConnection, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    }
}

void PhpTcpServer::onAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "SimpleTcpSocketServerDemo::displayError " << socketError;
}

void PhpTcpServer::onReadyRead()
{
    QTcpSocket* pClientConnection = dynamic_cast<QTcpSocket*>(sender());
    QString data = pClientConnection->readAll();
    qDebug()<<"got:"<<data<<"from client"<<endl;
    pClientConnection->write("i got it");
    pClientConnection->flush();
    pClientConnection->close();
}

PhpTcpServer::~PhpTcpServer()
{
    if (m_pTcpServer) {
        m_pTcpServer->close();
        m_pTcpServer->deleteLater();
        m_pTcpServer = nullptr;
    }
}
