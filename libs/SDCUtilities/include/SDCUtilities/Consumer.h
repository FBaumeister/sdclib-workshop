/**
 * @brief Simply a wrapper class for an SDCConsumer with convenience functionalities.
 *
 * @class SDCUtilities::Consumer
 * @ingroup SDCUtilities
 *
 * @copyright 2021 SurgiTAIX AG
 *
 */
#ifndef SDCUTILITIES_CONSUMER_H
#define SDCUTILITIES_CONSUMER_H

#include "SDCUtilities/Prerequisites.h"

#include <SDCLib/Prerequisites.h>
#include <SDCLib/Data/SDC/SDCConsumer.h>

#include <memory>

namespace SDCUtilities
{
    class Consumer : public std::enable_shared_from_this<Consumer>
    {
        friend class ConnectionLostHandlerImpl;

    public:
        using EPR_t = std::string;
        using ConnectionLostCallback = std::function<void(void)>;


    private:
        // Some internal variables of the Stack to hold / wrap
        std::unique_ptr<SDCLib::Data::SDC::SDCConsumer> m_consumer{nullptr};
        std::shared_ptr<SDCLib::SDCInstance> m_SDCInstance{nullptr};  // Note::weak_ptr sufficient?
        EPR_t m_EPR;

        /** Registered with the Participant Monitoring. Forwards the Connection-Lost detection. */
        std::unique_ptr<ConnectionLostHandlerImpl> m_lostHandler{nullptr};

        ConnectionLostCallback m_connectionLostCallback;

    public:
        static std::shared_ptr<Consumer> createNew(std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>);

        /** Only create as std::shared_ptr (use Consumer::createNew) -> Protect this and build proper factory (TBD) */
        Consumer(std::unique_ptr<SDCLib::Data::SDC::SDCConsumer>);
        ~Consumer();

        EPR_t getEPR() const;
        SDCLib::Data::SDC::SDCConsumer* getSDCConsumer() const noexcept;


        void registerConnectionLostCallback(ConnectionLostCallback p_callback)
        {
            m_connectionLostCallback = p_callback;
        }


    private:
        /** Init and configuration */
        void init();
        void createConnectionLostHandler();

        /** Internal notifications */
        void _onConnectionLost();
    };
}  // namespace SDCUtilities

#endif
