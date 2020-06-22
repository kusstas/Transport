#pragma once

#include <QMap>

#include "IDispatcher.h"


namespace transport
{
///
/// \brief The Dispatcher class - dispatch util by data
///
class Dispatcher : public IDispacther
{
public:
    Dispatcher() = default;

    ///
    /// \brief handle received data and invoke subscribed handler by meta
    /// \param data
    ///
    void handle(QByteArray const& data) const;

    // IDispacther interface
public:
    void subscribe(SendedObjectMeta const& meta, Handler const& handler) override;
    void unsubscribe(SendedObjectMeta const& meta) override;

private:
    void onUnhandledData(SendedObjectMeta const& meta, QByteArray const& data) const;

private:
    QMap<SendedObjectMeta, Handler> m_handlers;
};
}

