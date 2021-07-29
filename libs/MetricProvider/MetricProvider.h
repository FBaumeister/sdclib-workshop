/**
 * @brief Simple Wrapper class to hold an SDCProvider
 *
 * @class Workshop::MetricProvider
 *
 * @copyright 2021 SurgiTAIX AG
 *
 */
#ifndef WORKSHOP_METRICPROVIDER_H_
#define WORKSHOP_METRICPROVIDER_H_

#include "StateHandlerContainer.h"

#include <SDCLib/Data/SDC/SDC-fwd.h>

#include <string>
#include <memory>

namespace Workshop
{
    class MetricProvider
    {
    public:
        using EPR_t = std::string;
        using ProviderStateHandlerContainer = StateHandlerContainer<SDCLib::Data::SDC::SDCProviderStateHandler>;

    private:
        std::unique_ptr<SDCLib::Data::SDC::SDCProvider> m_provider;
        const std::string FILE_CACHED_MDIB{"referenceMDIB.xml"};

        std::unique_ptr<ProviderStateHandlerContainer> m_stateHandlerContainer;

    public:
        MetricProvider(std::shared_ptr<SDCLib::SDCInstance>, const EPR_t&);
        ~MetricProvider();

    private:
        
        void addStateHandler();
        
        void setDeviceCharacteristics();
        void loadMDIBFromFile();
    };

}  // namespace Workshop


#endif
