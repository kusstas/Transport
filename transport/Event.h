#pragma once

#include <serialization/SerializedObject.h>


namespace transport
{
///
/// \brief The Event class - base event class
///
class Event
{
public:
    SERIALIZED_OBJECT(Event)

    Event() = default;
};
}

///
/// \brief definition serialization of event, x - request name, args... - serialized members or parent of object passed via atributtes
/// \warning need define outside class
///
#define SERIALIZED_EVENT(x, ...)    SERIALIZED_OBJECT(x, SERIALIZED_NAMED_PARENT("event", ::transport::Event) __VA_OPT__(,) __VA_ARGS__)
