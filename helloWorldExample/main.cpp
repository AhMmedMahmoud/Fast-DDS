#include <csignal>
#include <stdexcept>
#include <thread>

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/log/Log.hpp>

#include "Application.hpp"
#include "CLIParser.hpp"

using eprosima::fastdds::dds::Log;

using namespace eprosima::fastdds::examples::hello_world;

std::function<void(int)> stop_app_handler;

void signal_handler(int signum)
{
    stop_app_handler(signum);
}

int main(int argc, char** argv)
{
    const std::string topic_name = "hello_world_topic";
    
    CLIParser::hello_world_config config = CLIParser::parse_cli_options(argc, argv);

    std::string app_name = CLIParser::parse_entity_kind(config.entity);

    std::shared_ptr<Application> app = Application::make_app(config, topic_name);

    std::thread thread(&Application::run, app);

    std::cout << app_name << " running. Please press Ctrl+C to stop the " << app_name << " at any time." << std::endl;
    
    stop_app_handler = [&](int signum)
    {
        std::cout << "\n" << CLIParser::parse_signal(signum) << " received, stopping " << app_name << " execution." << std::endl;
        app->stop();
    };

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGHUP, signal_handler);

    thread.join();

    Log::Reset();

    return 0;
}
