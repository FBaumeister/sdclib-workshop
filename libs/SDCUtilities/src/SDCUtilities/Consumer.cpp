#include "SDCUtilities/Consumer.h"
#include "SDCUtilities/ConnectionLostHandlerImpl.h"

#include <SDCLib/Prerequisites.h>
#include <SDCLib/SDCInstance.h>
#include <SDCLib/Data/SDC/SDCConsumer.h>

#include <cassert>
#include <stdexcept>
#include <memory>
#include <iostream>

using namespace SDCUtilities;

Consumer::Consumer(std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> p_consumer)
    : m_consumer(std::move(p_consumer))
{
    if(!m_consumer)
    {
        throw std::runtime_error{"Cannot create Consumer instance. Passed SDCConsumer pointer is nullptr."};
    }
}
Consumer::~Consumer()
{
}

std::shared_ptr<Consumer> Consumer::createNew(std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> p_consumer)
{
    auto newConsumer = std::make_shared<Consumer>(std::move(p_consumer));
    newConsumer->init();
    return newConsumer;
}

Consumer::EPR_t Consumer::getEPR() const
{
    return m_EPR;
}
SDCLib::Data::SDC::SDCConsumer* Consumer::getSDCConsumer() const noexcept
{
    return m_consumer.get();
}

void Consumer::init()
{
    // Basics (Configuration members etc.)
    m_EPR = m_consumer->getEndpointReference();
    m_SDCInstance = m_consumer->getSDCInstance();

    createConnectionLostHandler();
}
void Consumer::createConnectionLostHandler()
{
    // !WORKSHOP!
    assert(m_consumer);
    // Register the ConnectionLost Handling
    // Note: Due to async internal behavior pass a smart pointer
    m_lostHandler = std::make_unique<ConnectionLostHandlerImpl>(shared_from_this());
}
void Consumer::_onConnectionLost()
{
    if(!m_connectionLostCallback)
    {
        return;
    }

    // As this call may remove the las reference to this class
    // this may call the destructor -> create a temporary "keepAlive" pin
    auto keepAlive = shared_from_this();
    m_connectionLostCallback();
    keepAlive.reset();
}
