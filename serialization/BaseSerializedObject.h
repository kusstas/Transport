#pragma once

#include <QByteArray>


/// \brief utility for declare serialized varible of object
#define SERIALIZED_VAR(x)                   _SERIALIZED_VAR(x)

/// \brief utility for declare serialized varible of object by name
#define SERIALIZED_NAMED_VAR(n, x)          _SERIALIZED_NAMED_VAR(n, x)

/// \brief utility for declare serialized parent of object
#define SERIALIZED_PARENT(x)                _SERIALIZED_PARENT(x)

/// \brief utility for declare serialized parent of object by name
#define SERIALIZED_NAMED_PARENT(n, x)       _SERIALIZED_NAMED_PARENT(n, x)

///
/// \brief definition serialization of object, x - object name, args... - serialized members or parent of object passed via atributtes
/// \warning need define inside class
///
#define SERIALIZED_OBJECT(x, ...)           _SERIALIZED_OBJECT(x, __VA_ARGS__)

/// \brief utility for serialize varible on stream
#define SERIALIZED_VAR_ON_STREAM(x)         _SERIALIZED_VAR_ON_STREAM(x)

/// \brief utility for serialize varible on stream by name
#define SERIALIZED_NAMED_VAR_ON_STREAM(n, x) _SERIALIZED_NAMED_VAR_ON_STREAM(n, x)

/// \brief define stream
#define DEFINE_STREAM(x)                    namespace serialization { using SerializationStream = x; }

/// \brief define read stream holder
#define DEFINE_READ_STREAM_HOLDER(x)        namespace serialization { using ReadStreamHolder = ::so_impl::ReadStreamHolderRef<x, SerializationStream>; }

/// \brief define write stream holder
#define DEFINE_WRITE_STREAM_HOLDER(x)       namespace serialization { using WriteStreamHolder = ::so_impl::WriteStreamHolderRef<x, SerializationStream>; }


namespace so_impl
{
///
/// \brief The ReadStreamHolderRef struct - read stream holder
///
template <class Impl, class Stream>
struct ReadStreamHolderRef : private Impl
{
    ReadStreamHolderRef(QByteArray const& data)
        : Impl(data)
    {
    }

    Stream& stream()
    {
        return Impl::stream();
    }
};

///
/// \brief The WriteStreamHolderRef struct - write stream holder
///
template <class Impl, class Stream>
struct WriteStreamHolderRef : private Impl
{
    WriteStreamHolderRef() = default;

    Stream& stream()
    {
        return Impl::stream();
    }

    QByteArray data()
    {
        return Impl::data();
    }
};
}
