#pragma once

#include <QtWebSockets/QWebSocket>

#include "ISender.h"
#include "Dispatcher.h"


namespace transport
{
///
/// \brief The WebSocketSenderAdapter class - adapter of webocket for sender and dispatcher
///
class WebSocketSenderAdapter : public QObject, public ISender, public Dispatcher
{
    Q_OBJECT

public:
    WebSocketSenderAdapter(QWebSocket* socket, QObject* parent = nullptr);

    // ISender interface
public:
    void send(QByteArray data) override;

private slots:
    void onReceive(QByteArray const& data);

private:
    QWebSocket* m_socket;
};
}
