#ifndef FASTDDS_EXAMPLES_CPP_HELLO_WORLD__PUBLISHERAPP_HPP
#define FASTDDS_EXAMPLES_CPP_HELLO_WORLD__PUBLISHERAPP_HPP

#include <condition_variable>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "Application.hpp"
#include "CLIParser.hpp"
#include "HelloWorld.hpp"

using namespace eprosima::fastdds::dds;

namespace eprosima {
namespace fastdds {
namespace examples {
namespace hello_world {

class PublisherApp : public Application, public DataWriterListener
{
private:
    /************** dds classes **********/
    DomainParticipant* participant_;
    Publisher* publisher_;
    Topic* topic_;
    DataWriter* writer_;
    TypeSupport type_;

    /********** helper variables *********/
    int16_t matched_;
    std::atomic<bool> stop_;
    std::mutex mutex_;
    std::condition_variable cv_;

    /************** constants ************/
    const uint32_t period_ms_ = 100;

    /**************** data ***************/
    HelloWorld hello_;

    /********** helper functions **********/
    //! Return the current state of execution
    bool is_stopped();

    //! Publish a sample
    bool publish();

public:
    /************** constructor **********/
    PublisherApp(const std::string& topic_name);

    /************** deconstructor **********/
    ~PublisherApp();

    /*** implements virtual functions inherited from DataWriterListener ***/ 
    void on_publication_matched(
            DataWriter* writer,
            const PublicationMatchedStatus& info) override;

    /*** implements virtual functions inherited from application ***/       
    void run() override;
    void stop() override;
};

} // namespace hello_world
} // namespace examples
} // namespace fastdds
} // namespace eprosima

#endif // FASTDDS_EXAMPLES_CPP_HELLO_WORLD__PUBLISHERAPP_HPP
