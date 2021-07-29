#include "MetricProvider.h"

#include <SDCLib/SDCLibrary.h>
#include <SDCLib/SDCInstance.h>

#include <memory>
#include <iostream>

const std::string DEVICE_EPR("MetricProvider");

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

        std::cout << "MetricProvider" << std::endl;
        auto provider = std::make_unique<Workshop::MetricProvider>(instance, DEVICE_EPR);
        std::cout << "Press any key to exit..." << std::endl;
        std::cin.get();
        return 0;
    }
    catch(std::exception& e)
    {
        std::cout << "Failed to run MetricProvider: " << e.what() << std::endl;
    }
    return -1;
}
