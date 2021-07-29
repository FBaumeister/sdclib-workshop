#include "SDCUtilities/ConnectionLostHandlerImpl.h"

#include "SDCUtilities/Consumer.h"

#include <stdexcept>

using namespace SDCUtilities;

ConnectionLostHandlerImpl::ConnectionLostHandlerImpl(std::weak_ptr<Consumer> p_notifyTo)
    : m_notifyTo(p_notifyTo)
{
    if(auto locked = m_notifyTo.lock())
    {
        locked->getSDCConsumer()->setConnectionLostHandler(this);
    }
    else
    {
        throw std::runtime_error{"ConnectionLostHandlerImpl failed. Passed Consumer == nullptr"};
    }
}
void ConnectionLostHandlerImpl::onConnectionLost()
{
    if(auto locked = m_notifyTo.lock())
    {
        locked->_onConnectionLost();
    }
    else
    {
        throw std::runtime_error{"ConnectionLostHandlerImpl::onConnectionLost() failed. Passed Consumer == nullptr"};
    }
}