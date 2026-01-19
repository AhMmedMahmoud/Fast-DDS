#include <csignal>
#include <cstdlib>
#include <iostream>

#include <fastdds/dds/log/Log.hpp>

#ifndef FASTDDS_EXAMPLES_CPP_HELLO_WORLD__CLIPARSER_HPP
#define FASTDDS_EXAMPLES_CPP_HELLO_WORLD__CLIPARSER_HPP

namespace eprosima {
namespace fastdds {
namespace examples {
namespace hello_world {

using dds::Log;

class CLIParser
{
public:
    CLIParser() = delete;

    //! Entity kind enumeration
    enum class EntityKind : uint8_t
    {
        PUBLISHER,
        SUBSCRIBER,
        UNDEFINED
    };

    //! Configuration structure for the application
    struct hello_world_config
    {
        CLIParser::EntityKind entity = CLIParser::EntityKind::UNDEFINED;
    };

    /**
     * @brief Parse the command line options and return the configuration_config object
     *
     * @param argc number of arguments
     * @param argv array of arguments
     * @return configuration_config object with the parsed options
     *
     * @warning This method finishes the execution of the program if the input arguments are invalid
     */
    static hello_world_config parse_cli_options(int argc, char* argv[])
    {
        hello_world_config config;

        std::string first_argument = argv[1];

        if (first_argument == "publisher" )
        {
            config.entity = CLIParser::EntityKind::PUBLISHER;
        }
        else if (first_argument == "subscriber")
        {
            config.entity = CLIParser::EntityKind::SUBSCRIBER;
        }
        
        return config;
    }

    /**
     * @brief Parse the signal number into the signal name
     *
     * @param signum signal number
     * @return std::string signal name
     */
    static std::string parse_signal(const int& signum)
    {
        switch (signum)
        {
            case SIGINT:
                return "SIGINT";
            case SIGTERM:
                return "SIGTERM";
            case SIGQUIT:
                return "SIGQUIT";
            case SIGHUP:
                return "SIGHUP";
            default:
                return "UNKNOWN SIGNAL";
        }
    }

    /**
     * @brief Parse the entity kind into std::string
     *
     * @param entity entity kind
     * @return std::string entity kind
     */
    static std::string parse_entity_kind(const EntityKind& entity)
    {
        switch (entity)
        {
            case EntityKind::PUBLISHER:
                return "Publisher";
            case EntityKind::SUBSCRIBER:
                return "Subscriber";
            case EntityKind::UNDEFINED:
            default:
                return "Undefined entity";
        }
    }

};

} // namespace hello_world
} // namespace examples
} // namespace fastdds
} // namespace eprosima

#endif // FASTDDS_EXAMPLES_CPP_HELLO_WORLD__CLIPARSER_HPP
