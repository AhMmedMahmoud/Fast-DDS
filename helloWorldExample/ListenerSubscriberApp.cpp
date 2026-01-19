#include "ListenerSubscriberApp.hpp"

#include <condition_variable>
#include <stdexcept>

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/core/status/SubscriptionMatchedStatus.hpp>

#include "CLIParser.hpp"
#include "HelloWorldPubSubTypes.hpp"
#include "Application.hpp"

using namespace eprosima::fastdds::dds;

namespace eprosima {
namespace fastdds {
namespace examples {
namespace hello_world {

/************** constructor **********/
ListenerSubscriberApp::ListenerSubscriberApp(const std::string& topic_name)
    : participant_(nullptr)
    , subscriber_(nullptr)
    , topic_(nullptr)
    , reader_(nullptr)
    , type_(new HelloWorldPubSubType())
    , received_samples_(0)
    , stop_(false)
{
    // Create the participant
    auto factory = DomainParticipantFactory::get_instance();
    participant_ = factory->create_participant_with_default_profile(nullptr, StatusMask::none());
    if (participant_ == nullptr)
    {
        throw std::runtime_error("Participant initialization failed");
    }

    // Create the subscriber
    SubscriberQos sub_qos = SUBSCRIBER_QOS_DEFAULT;
    participant_->get_default_subscriber_qos(sub_qos);
    subscriber_ = participant_->create_subscriber(sub_qos, nullptr, StatusMask::none());
    if (subscriber_ == nullptr)
    {
        throw std::runtime_error("Subscriber initialization failed");
    }

    // Register the type
    type_.register_type(participant_);

    // Create the topic
    TopicQos topic_qos = TOPIC_QOS_DEFAULT;
    participant_->get_default_topic_qos(topic_qos);
    topic_ = participant_->create_topic(topic_name, type_.get_type_name(), topic_qos);
    if (topic_ == nullptr)
    {
        throw std::runtime_error("Topic initialization failed");
    }

    // Create the reader
    DataReaderQos reader_qos = DATAREADER_QOS_DEFAULT;
    subscriber_->get_default_datareader_qos(reader_qos);
    reader_ = subscriber_->create_datareader(topic_, reader_qos, this, StatusMask::all());
    if (reader_ == nullptr)
    {
        throw std::runtime_error("DataReader initialization failed");
    }
}

/************** deconstructor **********/
ListenerSubscriberApp::~ListenerSubscriberApp()
{
    if (nullptr != participant_)
    {
        // Delete DDS entities contained within the DomainParticipant
        participant_->delete_contained_entities();

        // Delete DomainParticipant
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }
}

/*** implements virtual functions inherited from DataReaderListener ***/ 
void ListenerSubscriberApp::on_data_available(
        DataReader* reader)
{
    SampleInfo info;
    while ((!is_stopped()) && (RETCODE_OK == reader->take_next_sample(&hello_, &info)))
    {
        if ((info.instance_state == ALIVE_INSTANCE_STATE) && info.valid_data)
        {
            received_samples_++;
            // Print Hello world message data
            std::cout << "Message: '" << hello_.message() << "' with index: '" << hello_.index() << "' RECEIVED" << std::endl;
        }
    }
}

void ListenerSubscriberApp::on_subscription_matched(
    DataReader* /*reader*/,
    const SubscriptionMatchedStatus& info)
{
    if (info.current_count_change == 1)
    {
        std::cout << "Subscriber matched." << std::endl;
    }
    else if (info.current_count_change == -1)
    {
        std::cout << "Subscriber unmatched." << std::endl;
    }
}

/*** implements virtual functions inherited from application ***/  
void ListenerSubscriberApp::run()
{
    std::unique_lock<std::mutex> lck(terminate_cv_mtx_);
    terminate_cv_.wait(lck, [&]
            {
                return is_stopped();
            });
}

void ListenerSubscriberApp::stop()
{
    stop_.store(true);
    terminate_cv_.notify_all();
}

/********** helper functions **********/
bool ListenerSubscriberApp::is_stopped()
{
    return stop_.load();
}

} // namespace hello_world
} // namespace examples
} // namespace fastdds
} // namespace eprosima
