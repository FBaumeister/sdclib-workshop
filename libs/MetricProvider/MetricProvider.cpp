#include "MetricProvider.h"

#include "StateHandler.h"

#include <SDCLib/SDCLibrary.h>
#include <SDCLib/SDCInstance.h>
#include <SDCLib/Data/SDC/SDCProvider.h>
#include <SDCLib/Data/SDC/MDIB/MdDescription.h>
#include <SDCLib/Data/SDC/MDIB/NumericMetricDescriptor.h>

#include <cassert>
#include <fstream>

using namespace Workshop;

MetricProvider::MetricProvider(std::shared_ptr<SDCLib::SDCInstance> p_SDCInstance, const EPR_t& p_EPR)
    : m_provider(std::make_unique<SDCLib::Data::SDC::SDCProvider>(p_SDCInstance))
    , m_stateHandlerContainer(std::make_unique<ProviderStateHandlerContainer>())
{
    m_provider->setEndpointReferenceByName(p_EPR);

    setDeviceCharacteristics();
    loadMDIBFromFile();

    addStateHandler();

    m_provider->startup();
}
MetricProvider::~MetricProvider() = default;

void MetricProvider::addStateHandler()
{
    using StateType = SDCLib::Data::SDC::NumericMetricState;
    const auto& relevantStates = m_provider->getMdDescription().collectAllNumericMetricDescriptors();

    bool settable{false};
    for(const auto& state : relevantStates)
    {
        auto handler = std::make_shared<DefaultNumericStateHandler>(state.getHandle(), settable);
        m_stateHandlerContainer->registerHandler(handler);
        std::cout << "Added StateHandler for NumericMetric: " << state.getHandle() << std::endl;
    }
}

void MetricProvider::setDeviceCharacteristics()
{
    assert(m_provider);

    // set DPWS metadata, e.g. for the displayed friendly name
    SDCLib::Dev::DeviceCharacteristics devChar;
    devChar.addFriendlyName("en", "Workshop Demo Provider");
    m_provider->setDeviceCharacteristics(devChar);
}
void MetricProvider::loadMDIBFromFile()
{
    assert(m_provider);

    std::ifstream filestream{FILE_CACHED_MDIB};
    if(!filestream.is_open())
    {
        throw std::runtime_error{"MDIB not found!"};
    }

    std::stringstream buffer;
    buffer << filestream.rdbuf();
    std::string mdDesciption_xml = buffer.str();
    filestream.close();

    m_provider->setMdDescription(mdDesciption_xml);
}