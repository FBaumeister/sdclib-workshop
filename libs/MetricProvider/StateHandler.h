/**
 * @brief Some predefined StateHandlers
 *
 * @class SDCUtilities::StateHandler::StateHandlerContainer
 * @ingroup SDCUtilities
 *
 * @copyright 2021 SurgiTAIX AG
 *
 */
#ifndef WORKSHOP_STATEHANDLER_H_
#define WORKSHOP_STATEHANDLER_H_

#include <SDCLib/Data/SDC/SDCProviderStateHandler.h>
#include <SDCLib/Data/SDC/SDCProviderMDStateHandler.h>
#include <SDCLib/Data/SDC/MDIB/NumericMetricState.h>
#include <SDCLib/Data/SDC/MDIB/NumericMetricState.h>
#include <SDCLib/Data/SDC/MDIB/NumericMetricValue.h>
#include <SDCLib/Data/SDC/MDIB/custom/OperationInvocationContext.h>

#include <string>
#include <iostream>

namespace Workshop
{
    class DefaultNumericStateHandler : public SDCLib::Data::SDC::SDCProviderMDStateHandler<SDCLib::Data::SDC::NumericMetricState>
    {
    private:
        const bool m_settable{false};

    public:
        DefaultNumericStateHandler(const std::string p_descriptorHandle, bool settable)
            : SDCProviderMDStateHandler(p_descriptorHandle)
            , m_settable(settable)
        {
        }

        // Helper method
        SDCLib::Data::SDC::NumericMetricState createState(double p_initialValue)
        {
            SDCLib::Data::SDC::NumericMetricState newState{getDescriptorHandle()};
            /*newState.setMetricValue(SDCLib::Data::SDC::NumericMetricValue(MetricQuality(SDCLib::Data::SDC::MeasurementValidity::Vld)).setValue(p_initialValue))
                .setActivationState(SDCLib::Data::SDC::ComponentActivation::On);*/
            return newState;
        }

        // define how to react on a request for a state change.
        SDCLib::Data::SDC::InvocationState onStateChangeRequest(const SDCLib::Data::SDC::NumericMetricState& p_state,
                                                                const SDCLib::Data::SDC::OperationInvocationContext& p_oic) override
        {
            if(!m_settable)
            {
                // extract information from the incoming operation
                std::cout << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
                return SDCLib::Data::SDC::InvocationState::Fail;
            }
            else
            {
                // Invocation has been fired as WAITING when entering this method
                notifyOperationInvoked(p_oic, SDCLib::Data::SDC::InvocationState::Start);
                // Do stuff
                std::cout << "Provider: handle_set received state change request.";
                std::cout << "State's value: " << p_state.getMetricValue().getValue() << std::endl;
                // extract information from the incoming operation
                std::cout << "Operation invoked. Handle: " << p_oic.operationHandle << std::endl;
                // if success return Finished
                // Framework will update internal MDIB with the state's value and increase MDIB version
                return SDCLib::Data::SDC::InvocationState::Fin;
            }
        }


        SDCLib::Data::SDC::NumericMetricState getInitialState() override
        {
            return createState(0.0);
        }

        void setNumericValue(double p_newValue)
        {
            auto newState{createState(p_newValue)};
            updateState(newState);
        }
    };

}  // namespace Workshop

#endif
