#include "SDCUtilities/Consumer.h"

#include <SDCLib/SDCLibrary.h>
#include <SDCLib/SDCInstance.h>
#include <SDCLib/Prerequisites.h>
#include <OSELib/SDC/ServiceManager.h>

#include <cassert>
#include <memory>
#include <thread>
#include <stdexcept>
#include <signal.h>
#include <iostream>

const auto DISCOVERY_TIMEOUT{std::chrono::milliseconds{2000}};

// Qnd
std::atomic<bool> APPLICATION_RUNNING{false};
void consolehandler(int)
{
    std::cout << "\nExit. Performing Cleanup..." << std::endl;
    APPLICATION_RUNNING = false;
}
void start()
{
    // Demonstration purpose
    SDCLib::SDCLibrary::getInstance().startup(OSELib::LogLevel::None);

    APPLICATION_RUNNING = true;

    // Init ConsoleHandler to capture interrupts
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = consolehandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}
void abortApplication()
{
    APPLICATION_RUNNING = false;
}
bool isApplicationRunning()
{
    return APPLICATION_RUNNING;
}

void onConnectionLost()
{
    std::cout << "onConnectionLost called!" << std::endl;
    abortApplication();
}

std::shared_ptr<SDCUtilities::Consumer> discoverAndConnect(OSELib::SDC::ServiceManager& p_SDCServiceManager)
{
    std::cout << "Starting Discovery...";
    const auto waitNumLoops = DISCOVERY_TIMEOUT.count() / 100 + 5;
    auto asyncResults = p_SDCServiceManager.async_discover();

    for(auto i = 0; i < waitNumLoops; ++i)
    {
        if(!isApplicationRunning())
        {
            std::cout << "\nDiscover Abort!\n";
            return nullptr;
        }
        std::cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(DISCOVERY_TIMEOUT / waitNumLoops));
    }

    auto results = asyncResults.get();
    std::cout << "\nDISCOVERED: ";
    if(results.empty())
    {
        std::cout << "None.\n";
        return nullptr;
    }

    std::cout << results.size() << ":" << std::endl;

    std::size_t counter{1};
    for(const auto& consumer : results)
    {
        if(!consumer)
        {
            continue;
        }
        std::cout << counter++ << ". " << consumer->getEndpointReference() << std::endl;
        consumer->disconnect();
    }

    std::string deviceNumber;
    std::cout << "Enter Device Number: ";
    getline(std::cin, deviceNumber);

    int number{0};
    try
    {
        number = std::stoi(deviceNumber.c_str());
    }
    catch(...)
    {
        std::cout << "Entered value invalid!" << std::endl;
        return nullptr;
    }
    number--;  // Must be indexing an array

    if((number < 0) || (number >= results.size()))
    {
        std::cout << "Entered value out of range!" << std::endl;
        return nullptr;
    }

    // Connect
    auto deviceName = results.at(number)->getEndpointReference();

    std::cout << "Connecting to " << deviceName << "..." << std::flush;
    try
    {
        auto resolvedConsumer = p_SDCServiceManager.discoverEndpointReference(deviceName);
        auto newConsumer = SDCUtilities::Consumer::createNew(std::move(resolvedConsumer));
        newConsumer->registerConnectionLostCallback(&onConnectionLost);
        return newConsumer;
    }
    catch(std::exception& e)
    {
        std::cout << "\nFailed to connect with Reason: " << e.what() << std::endl;
    }
    return nullptr;
}

int main()
{
    start();

    auto SDCInstance = std::make_shared<SDCLib::SDCInstance>(false);
    SDCInstance->setIP6enabled(false);
    SDCInstance->setDiscoveryTime(DISCOVERY_TIMEOUT);
    SDCInstance->init();
    std::cout << "Binding SDCInstance to Default Network Interface... ";
    if(!SDCInstance->bindToDefaultNetworkInterface())
    {
        std::cout << "\nFailed to bind to NetworkInterface\n";
        return -1;
    }
    std::cout << "done !" << std::endl;


    // ServiceManager
    std::cout << "Creating ServiceManager... ";
    OSELib::SDC::ServiceManager SDCServiceManager(SDCInstance);
    std::cout << "done !" << std::endl;

    auto consumer = discoverAndConnect(SDCServiceManager);
    if(!consumer)
    {
        std::cout << "Exiting" << std::endl;
        return -1;
    }
    std::cout << "\nDone !" << std::endl;


    std::cout << "Waiting for Provider to exit..." << std::endl;
    // Wait until the provider quits
    while(isApplicationRunning())
        ;

    std::cout << "Application Exit." << std::endl;
    return 0;
}
