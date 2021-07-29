/**
 * @brief Handler to get notified when a connected SDCConsumer detects a connection loss.
 *
 * @class SDCUtilities::ConnectionLostHandlerImpl
 * @ingroup SDCUtilities
 *
 * @copyright 2021 SurgiTAIX AG
 *
 */
#ifndef SDCUTILITIES_CONNECTIONLOSTHANDLERIMPL_H
#define SDCUTILITIES_CONNECTIONLOSTHANDLERIMPL_H

#include "SDCUtilities/Prerequisites.h"

#include <SDCLib/Data/SDC/SDCConsumerConnectionLostHandler.h>

namespace SDCUtilities
{
    class ConnectionLostHandlerImpl : public SDCLib::Data::SDC::SDCConsumerConnectionLostHandler
    {
    public:
        using EPR_t = std::string;

    private:
        std::weak_ptr<Consumer> m_notifyTo;

    public:
        ConnectionLostHandlerImpl(std::weak_ptr<Consumer>);

        void onConnectionLost() override;
    };

}  // namespace SDCUtilities

#endif
