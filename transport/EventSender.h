#pragma once

#include <type_traits>
#include <cassert>

#include "SendedObjectMeta.h"
#include "ISender.h"
#include "Event.h"


namespace transport
{
///
/// \brief The EventSender class - event sender
/// \param T - event type
/// \warning T should be devired of transport::Event
///
template <class T>
class EventSender
{
    static_assert(std::is_base_of<Event, T>::value, "T should be devired of transport::Event");

public:
    ///
    /// \brief EventSender
    /// \param sender - sender of date
    ///
    EventSender(ISender* sender)
        : m_meta(SendedObjectMeta::create<T>())
        , m_sender(sender)
    {
        assert(sender);
    }

    virtual ~EventSender() {};

    ///
    /// \brief notify about event EventHandler
    /// \param event
    ///
    void notify(T const& event)
    {
        serialization::WriteStreamHolder holder;
        holder.stream() << SERIALIZED_NAMED_VAR_ON_STREAM(META_VAR_NAME, m_meta)
                        << SERIALIZED_NAMED_VAR_ON_STREAM(ARG_VAR_NAME, event);
        m_sender->send(holder.data());
    }

private:
    SendedObjectMeta m_meta;
    ISender* m_sender;
};
}
