#pragma once

#include <serialization/SerializedObject.h>


namespace transport
{
///
/// \brief The Response class - base response class
/// @property id - request id
///
class Response
{
public:
    SERIALIZED_OBJECT(Response, SERIALIZED_VAR(id), SERIALIZED_VAR(success))

    quint64 id = 0;
    bool success = false;
};

}

///
/// \brief definition serialization of response, x - request name, args... - serialized members or parent of object passed via atributtes
/// \warning need define outside class
///
#define SERIALIZED_RESPONSE(x, ...)   SERIALIZED_OBJECT(x, SERIALIZED_NAMED_PARENT("response", ::transport::Response) __VA_OPT__(,) __VA_ARGS__)
