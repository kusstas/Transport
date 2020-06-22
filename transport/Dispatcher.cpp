#include "Dispatcher.h"

#include <QDebug>


namespace transport
{
void Dispatcher::handle(QByteArray const& data) const
{
    serialization::ReadStreamHolder holder(data);
    transport::SendedObjectMeta meta;
    holder.stream() >> SERIALIZED_NAMED_VAR_ON_STREAM(META_VAR_NAME, meta);

    auto const& handler = m_handlers.value(meta, [this, &meta, &data] (serialization::SerializationStream&)
    {
        onUnhandledData(meta, data);
    });

    handler(holder.stream());
}

void Dispatcher::subscribe(SendedObjectMeta const& meta, Handler const& handler)
{
    Handler& ref = m_handlers[meta];

    if (ref)
    {
        qWarning() << "Handle alredy subscribed by:" << meta.id;
    }
    else
    {
        ref = handler;
    }
}

void Dispatcher::unsubscribe(SendedObjectMeta const& meta)
{
    m_handlers.remove(meta);
}

void Dispatcher::onUnhandledData(SendedObjectMeta const& meta, QByteArray const& data) const
{
    qWarning() << "Unhandled data, id:" << meta.id << "data:" << data;
}
}
