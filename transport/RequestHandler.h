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
/// \brief The RequestHandler class
/// \param _Request - request type
/// \param _Response - response type
/// \warning _Request should be devired of transport::Request
/// \warning _Response should be devired of transport::Response
///
template <class _Request, class _Response>
class RequestHandler
{
    static_assert(std::is_base_of<Request, _Request>::value, "_Request should be devired of transport::Request");
    static_assert(std::is_base_of<Response, _Response>::value, "_Response should be devired of transport::Response");

public:
    ///
    /// \brief RequestHandler
    /// \param sender - sender of data
    /// \param dispatcher - dispatcher of received data
    ///
    RequestHandler(ISender* sender, IDispacther* dispacther)
        : m_requestMeta(SendedObjectMeta::create<_Request>())
        , m_responseMeta(SendedObjectMeta::create<_Response>())
        , m_sender(sender)
        , m_dispacther(dispacther)
    {
        assert(sender && dispacther);

        m_dispacther->subscribe(m_requestMeta.id, [this] (serialization::SerializationStream& stream)
        {
            _Request request;
            stream >> SERIALIZED_NAMED_VAR_ON_STREAM(ARG_VAR_NAME, request);
            onRequest(request);
        });
    }

    virtual ~RequestHandler()
    {
        m_dispacther->unsubscribe(m_requestMeta.id);
    }

    ///
    /// \brief response on received request
    /// \param response
    ///
    void response(_Response const& response)
    {
        serialization::WriteStreamHolder holder;
        holder.stream() << SERIALIZED_NAMED_VAR_ON_STREAM(META_VAR_NAME, m_responseMeta)
                        << SERIALIZED_NAMED_VAR_ON_STREAM(ARG_VAR_NAME, response);
        m_sender->send(holder.data());
    }

protected:
    ///
    /// \brief onRequest - invokes upon request sender invoke send
    /// \param request
    ///
    virtual void onRequest(_Request const& request) = 0;

private:
    SendedObjectMeta const m_requestMeta;
    SendedObjectMeta const m_responseMeta;

    ISender* m_sender;
    IDispacther* m_dispacther;
};
}
