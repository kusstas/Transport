#pragma once

#include <type_traits>
#include <QDataStream>
#include <QBuffer>

#include "BaseSerializedObject.h"


namespace qbin_so_impl
{
///
/// \brief The ReadStreamHolderImpl class
///
class ReadStreamHolderImpl
{
public:
    ReadStreamHolderImpl(QByteArray const& data)
        : m_data(data)
        , m_stream(m_data)
    {
    }

    QDataStream& stream()
    {
        return m_stream;
    }

private:
    QByteArray m_data;
    QDataStream m_stream;
};

///
/// \brief The WriteStreamHolderImpl class
///
class WriteStreamHolderImpl
{
public:
    WriteStreamHolderImpl()
        : m_stream(&m_buffer)
    {
        m_buffer.open(QIODevice::WriteOnly);
    }

    QDataStream& stream()
    {
        return m_stream;
    }

    QByteArray data()
    {
        return m_buffer.data();
    }

private:
    QBuffer m_buffer;
    QDataStream m_stream;
};

/// \brief serialize empty args dummy
inline QDataStream& serialize(QDataStream& stream)
{
    return stream;
}

/// \brief deserialize empty args dummy
inline QDataStream& deserialize(QDataStream& stream)
{
    return stream;
}

/// \brief serialize all args(head & tail) to QDataStream
template <class Head, class... Tail>
QDataStream& serialize(QDataStream& stream, Head const& head, Tail const&... tail)
{
    stream << head;
    return serialize(stream, tail...);
}

/// \brief deserialize all args(head & tail) to QDataStream
template <class Head, class... Tail>
QDataStream& deserialize(QDataStream& stream, Head& head, Tail&... tail)
{
    stream >> head;
    return deserialize(stream, tail...);
}
}

DEFINE_STREAM(QDataStream)
DEFINE_READ_STREAM_HOLDER(qbin_so_impl::ReadStreamHolderImpl)
DEFINE_WRITE_STREAM_HOLDER(qbin_so_impl::WriteStreamHolderImpl)

/// \brief utility for declare serialized varible of object
#define _SERIALIZED_VAR(x)                object.x

/// \brief utility for declare serialized varible of object
#define _SERIALIZED_NAMED_VAR(n, x)       object.x

/// \brief utility for declare serialized parent of object
#define _SERIALIZED_PARENT(x)             static_cast<typename std::conditional<std::is_const<typename std::remove_reference<decltype(object)>::type>::value, x const&, x&>::type>(object)

/// \brief utility for declare serialized parent of object
#define _SERIALIZED_NAMED_PARENT(n, x)    static_cast<typename std::conditional<std::is_const<typename std::remove_reference<decltype(object)>::type>::value, x const&, x&>::type>(object)

/// \brief utility for serialize varible on stream
#define _SERIALIZED_VAR_ON_STREAM(x)            x

/// \brief utility for serialize varible on stream by name
#define _SERIALIZED_NAMED_VAR_ON_STREAM(n, x)   x

///
/// \brief definition serialization of object, x - object name, args... - serialized members or parent of object passed via atributtes
/// \warning need define inside class
///
#define _SERIALIZED_OBJECT(x, ...) \
    friend QDataStream& operator <<(QDataStream& stream, x const& object) { \
        Q_UNUSED(object); \
        return ::qbin_so_impl::serialize(stream __VA_OPT__(,) __VA_ARGS__); \
    } \
    friend QDataStream& operator >>(QDataStream& stream, x& object) { \
        Q_UNUSED(object); \
        return ::qbin_so_impl::deserialize(stream __VA_OPT__(,) __VA_ARGS__); \
    }
