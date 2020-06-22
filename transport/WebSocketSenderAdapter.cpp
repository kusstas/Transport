#include "WebSocketSenderAdapter.h"


namespace transport
{
WebSocketSenderAdapter::WebSocketSenderAdapter(QWebSocket* socket, QObject* parent)
    : QObject(parent)
    , m_socket(socket)
{
    assert(socket);

    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &WebSocketSenderAdapter::onReceive);
}

void WebSocketSenderAdapter::send(QByteArray data)
{
    m_socket->sendBinaryMessage(data);
}

void WebSocketSenderAdapter::onReceive(QByteArray const& data)
{
    Dispatcher::handle(data);
}
}
