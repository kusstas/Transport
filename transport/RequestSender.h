#pragma once

#include <type_traits>
#include <cassert>

#include "SendedObjectMeta.h"
#include "ISender.h"
#include "IDispatcher.h"
#include "Request.h"
#include "Response.h"


namespace transport
{
///
/// \brief The RequestSender class
/// \param _Request - request type
/// \param _Response - response type
/// \warning _Request should be devired of transport::Request
/// \warning _Response should be devired of transport::Response
///
template <class _Request, class _Response>
class RequestSender
{
    static_assert(std::is_base_of<Request, _Request>::value, "_Request should be devired of transport::Request");
    static_assert(std::is_base_of<Response, _Response>::value, "_Response should be devired of transport::Response");

public:
    ///
    /// \brief RequestSender
    /// \param sender - sender of data
    /// \param dispatcher - dispatcher of received data
    ///
    RequestSender(ISender* sender, IDispacther* dispacther)
        : m_requestMeta(SendedObjectMeta::create<_Request>())
        , m_responseMeta(SendedObjectMeta::create<_Response>())
        , m_sender(sender)
        , m_dispacther(dispacther)
    {
        assert(sender && dispacther);

        m_dispacther->subscribe(m_responseMeta, [this] (serialization::SerializationStream& stream)
        {
            _Response response;
            stream >> SERIALIZED_NAMED_VAR_ON_STREAM(ARG_VAR_NAME, response);
            onResponse(response);
        });
    }

    virtual ~RequestSender()
    {
        m_dispacther->unsubscribe(m_responseMeta);
    }

    ///
    /// \brief send request to RequestHandler
    /// \param request
    ///
    void send(_Request const& request)
    {
        serialization::WriteStreamHolder holder;
        holder.stream() << SERIALIZED_NAMED_VAR_ON_STREAM(META_VAR_NAME, m_requestMeta)
                        << SERIALIZED_NAMED_VAR_ON_STREAM(ARG_VAR_NAME, request);;
        m_sender->send(holder.data());
    }

protected:
    ///
    /// \brief onResponse - invokes upon RequestHandler return response
    /// \param response
    ///
    virtual void onResponse(_Response const& response) = 0;

private:
    SendedObjectMeta const m_requestMeta;
    SendedObjectMeta const m_responseMeta;

    ISender* m_sender;
    IDispacther* m_dispacther;
};
}
