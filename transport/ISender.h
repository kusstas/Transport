#pragma once

#include <QByteArray>


namespace transport
{
///
/// \brief The ISender class - interface for sending data
///
class ISender
{
public:
    virtual ~ISender() {}

    ///
    /// \brief send data
    /// \param data
    ///
    virtual void send(QByteArray data) = 0;
};
}
