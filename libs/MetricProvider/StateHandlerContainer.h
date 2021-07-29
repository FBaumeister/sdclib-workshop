/**
 * @brief Container to hold SDC StateHandlers (convenience class)
 *
 * @class Workshop::StateHandlerContainer
 *
 * @copyright 2021 SurgiTAIX AG
 *
 */
#ifndef WORKSHOP_STATEHANDLERCONTAINER_H_
#define WORKSHOP_STATEHANDLERCONTAINER_H_

#include <SDCLib/Prerequisites.h>
#include <SDCLib/Data/SDC/SDCConsumerOperationInvokedHandler.h>

#include <memory>
#include <vector>

namespace Workshop
{
    template<typename StateHandlerType> class StateHandlerContainer
    {
    public:
        using StateHandler_t = StateHandlerType;

    private:
        std::vector<std::shared_ptr<StateHandler_t>> m_registeredHandler;

    public:
        template<typename EventHandlerType> void registerHandler(EventHandlerType p_handler)
        {
            m_registeredHandler.push_back(std::static_pointer_cast<StateHandler_t>(p_handler));
        }

        std::vector<StateHandler_t*> getAllRegisteredHandlers()
        {
            std::vector<StateHandler_t*> rawPointer;
            for(auto& handler : m_registeredHandler)
            {
                rawPointer.push_back(handler.get());
            }

            return rawPointer;
        }

        template<typename HandlerType> std::vector<HandlerType*> getRegisteredEventHandlerByType()
        {
            std::vector<HandlerType*> collectedHandlers;
            for(auto& handler : m_registeredHandler)
            {
                if(auto casted = dynamic_cast<HandlerType*>(handler.get()))
                {
                    collectedHandlers.push_back(casted);
                }
            }
            return collectedHandlers;
        }
    };

}  // namespace Workshop


#endif
