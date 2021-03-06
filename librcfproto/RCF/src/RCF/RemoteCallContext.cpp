
#include <RCF/RemoteCallContext.hpp>
#include <RCF/AsioServerTransport.hpp>

namespace RCF {

    RemoteCallContextImpl::RemoteCallContextImpl(RCF::RcfSession & session) : mCommitted(false)
    {
        mRcfSessionPtr = session.shared_from_this();
        mRcfSessionPtr->mAutoSend = false;

        mpParametersUntyped = mRcfSessionPtr->mpParameters;

        AsioSessionState & sessionState =
            dynamic_cast<AsioSessionState &>(
            mRcfSessionPtr->getSessionState());

        mSessionStatePtr = sessionState.sharedFromThis();
    }

    void RemoteCallContextImpl::commit()
    {
        RCF_ASSERT(!mCommitted);

        if ( mRcfSessionPtr->mRequest.getOneway() )
        {
            RCF_LOG_3()(this) << "RcfServer - suppressing response to oneway call.";
            mRcfSessionPtr->mIn.clearByteBuffer();
            mRcfSessionPtr->clearParameters();
            setTlsRcfSessionPtr();
            mRcfSessionPtr->onWriteCompleted();
        }
        else
        {
            mRcfSessionPtr->sendResponse();
        }

        mpParametersUntyped = NULL;
        mRcfSessionPtr.reset();

        mSessionStatePtr.reset();

        mCommitted = true;
    }

    void RemoteCallContextImpl::commit(const std::exception &e)
    {
        RCF_ASSERT(!mCommitted);

        if ( mRcfSessionPtr->mRequest.getOneway() )
        {
            RCF_LOG_3()(this) << "RcfServer - suppressing response to oneway call.";
            mRcfSessionPtr->mIn.clearByteBuffer();
            mRcfSessionPtr->clearParameters();
            setTlsRcfSessionPtr();
            mRcfSessionPtr->onWriteCompleted();
        }
        else
        {
            mRcfSessionPtr->sendResponseException(e);
        }

        mpParametersUntyped = NULL;
        mRcfSessionPtr.reset();

        mSessionStatePtr.reset();

        mCommitted = true;
    }

    bool RemoteCallContextImpl::isCommitted() const
    {
        return mCommitted;
    }


} // namespace RCF
