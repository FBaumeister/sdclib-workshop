
#include <SDCLib/SDCLibrary.h>
#include <SDCLib/SDCInstance.h>
#include <SDCLib/Data/SDC/SDCProvider.h>

#include <memory>
#include <fstream>
#include <iostream>

const std::string DEVICE_EPR("UDI-BasicProvider");

class BasicProvider
{
private:
    SDCLib::Data::SDC::SDCProvider m_provider;
    const std::string FILE_CACHED_MDIB{"referenceMDIB.xml"};

public:
    BasicProvider(std::shared_ptr<SDCLib::SDCInstance> p_SDCInstance)
        : m_provider(p_SDCInstance)
    {
        m_provider.setEndpointReferenceByName(DEVICE_EPR);

        // set DPWS metadata, e.g. for the displayed friendly name
        SDCLib::Dev::DeviceCharacteristics devChar;
        devChar.addFriendlyName("en", "Workshop Demo Provider");
        m_provider.setDeviceCharacteristics(devChar);

        loadMDIBFromFile();

        m_provider.startup();
    }


private:
    void loadMDIBFromFile()
    {
        std::ifstream filestream{FILE_CACHED_MDIB};
        if(!filestream.is_open())
        {
            throw std::runtime_error{"MDIB not found!"};
        }

        std::stringstream buffer;
        buffer << filestream.rdbuf();
        std::string mdDesciption_xml = buffer.str();
        filestream.close();

        m_provider.setMdDescription(mdDesciption_xml);
    }
};


int main()
{
    try
    {
        // Demo-case
        SDCLib::SDCLibrary::getInstance().startup(OSELib::LogLevel::None);
        auto instance = std::make_shared<SDCLib::SDCInstance>(true);

        // Some restrictions
        instance->setIP6enabled(false);
        if(!instance->bindToDefaultNetworkInterface())
        {
            std::cout << "Failed to bind to default network interface! Exit..." << std::endl;
            return -1;
        }

        std::cout << "BasicProvider" << std::endl;
        auto provider = std::make_unique<BasicProvider>(instance);
        std::cout << "Press any key to exit..." << std::endl;
        std::cin.get();
        return 0;
    }
    catch(std::exception& e)
    {
        std::cout << "Failed to run Provider: " << e.what() << std::endl;
    }
    return -1;
}
