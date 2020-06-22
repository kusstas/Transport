#pragma once

#include <typeinfo>
#include <QString>
#include <serialization/SerializedObject.h>


namespace transport
{
constexpr auto META_VAR_NAME = "meta";
constexpr auto ARG_VAR_NAME = "arg";

///
/// \brief The SendedObjectMeta struct - meta of sended object
///
struct SendedObjectMeta
{
    SERIALIZED_OBJECT(SendedObjectMeta, SERIALIZED_VAR(id))

    template <class T>
    static SendedObjectMeta create()
    {
        return SendedObjectMeta(typeid(T).name());
    }

    SendedObjectMeta() = default;
    SendedObjectMeta(QString const& id)
        : id(id)
    {
    }

    ///
    /// \brief id - name of object
    ///
    QString id;
};

inline bool operator < (SendedObjectMeta const& l, SendedObjectMeta const& r)
{
    return l.id < r.id;
}
}
