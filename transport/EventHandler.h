#pragma once

#include <type_traits>
#include <cassert>

#include "SendedObjectMeta.h"
#include "IDispatcher.h"
#include "Event.h"


namespace transport
{
///
/// \brief The EventHandler class - event handler
/// \param T - event type
/// \warning T should be devired of transport::Event
///
template <class T>
class EventHandler
{
    static_assert(std::is_base_of<Event, T>::value, "T should be devired of transport::Event");

public:
    ///
    /// \brief EventHandler
    /// \param dispatcher - dispatcher of received data
    ///
    EventHandler(IDispacther* dispatcher)
        : m_meta(SendedObjectMeta::create<T>())
        , m_dispatcher(dispatcher)
    {
        assert(dispatcher);
        m_dispatcher->subscribe(m_meta, [this] (serialization::SerializationStream& stream)
        {
            T event;
            stream >> SERIALIZED_NAMED_VAR_ON_STREAM(ARG_VAR_NAME, event);
            onNotify(event);
        });
    }

    virtual ~EventHandler()
    {
        m_dispatcher->unsubscribe(m_meta);
    };

protected:
    ///
    /// \brief onNotify - invokes upon EventSender notify about event
    /// \param event
    ///
    virtual void onNotify(T const& event) = 0;

private:
    SendedObjectMeta const m_meta;
    IDispacther* m_dispatcher;
};
}
