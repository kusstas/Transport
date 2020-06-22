#pragma once

#include <serialization/SerializedObject.h>


namespace transport
{
///
/// \brief The Request class - base request class
/// @property id - request id
///
class Request
{
public:
    SERIALIZED_OBJECT(Request, SERIALIZED_VAR(id))

    quint64 id = 0;
};
}

///
/// \brief definition serialization of request, x - request name, args... - serialized members or parent of object passed via atributtes
/// \warning need define outside class
///
#define SERIALIZED_REQUEST(x, ...)     SERIALIZED_OBJECT(x, SERIALIZED_NAMED_PARENT("request", ::transport::Request) __VA_OPT__(,__VA_ARGS__))
