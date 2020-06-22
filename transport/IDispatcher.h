#pragma once

#include <functional>
#include <serialization/SerializedObject.h>

#include "SendedObjectMeta.h"

namespace transport
{
///
/// \brief The IDispacther class - interface of dispatcher received data
///
class IDispacther
{
public:
    ///
    /// \brief Handler of received data
    /// \param received data
    ///
    using Handler = std::function<void(serialization::SerializationStream&)>;

    virtual ~IDispacther() { }

    ///
    /// \brief subscribe handler on received data by object id
    /// \param meta - object meta
    /// \param handler
    ///
    virtual void subscribe(SendedObjectMeta const& meta, Handler const& handler) = 0;

    ///
    /// \brief unsubscribe handler on received data by object id
    /// \param meta - object meta
    ///
    virtual void unsubscribe(SendedObjectMeta const& meta) = 0;
};
}
