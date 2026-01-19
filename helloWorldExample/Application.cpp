#include "Application.hpp"

#include "CLIParser.hpp"
#include "ListenerSubscriberApp.hpp"
#include "PublisherApp.hpp"
// #include "WaitsetSubscriberApp.hpp"

using namespace eprosima::fastdds::dds;

namespace eprosima {
namespace fastdds {
namespace examples {
namespace hello_world {

//! Factory method to create a publisher or subscriber
std::shared_ptr<Application> Application::make_app(
        const CLIParser::hello_world_config& config,
        const std::string& topic_name)
{
    std::shared_ptr<Application> app;
    switch (config.entity)
    {
        case CLIParser::EntityKind::PUBLISHER:
            app = std::make_shared<PublisherApp>(topic_name);
            break;
        case CLIParser::EntityKind::SUBSCRIBER:
            app = std::make_shared<ListenerSubscriberApp>(topic_name);
            break;
        case CLIParser::EntityKind::UNDEFINED:
        default:
            throw std::runtime_error("Entity initialization failed");
            break;
    }
    return app;
}

} // namespace hello_world
} // namespace examples
} // namespace fastdds
} // namespace eprosima
