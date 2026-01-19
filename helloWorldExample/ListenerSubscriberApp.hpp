#ifndef FASTDDS_EXAMPLES_CPP_HELLO_WORLD__LISTENERSUBSCRIBERAPP_HPP
#define FASTDDS_EXAMPLES_CPP_HELLO_WORLD__LISTENERSUBSCRIBERAPP_HPP

#include <condition_variable>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "CLIParser.hpp"
#include "HelloWorld.hpp"
#include "Application.hpp"

using namespace eprosima::fastdds::dds;

namespace eprosima {
namespace fastdds {
namespace examples {
namespace hello_world {

class ListenerSubscriberApp : public Application,  public DataReaderListener
{
public:
    /************** constructor **********/
    ListenerSubscriberApp(const std::string& topic_name);

    /************** deconstructor **********/
    ~ListenerSubscriberApp();


    /*** implements virtual functions inherited from DataReaderListener ***/    
    //! Subscription callback
    void on_data_available(
        DataReader* reader) override;
                
    void on_subscription_matched(
            DataReader* reader,
            const SubscriptionMatchedStatus& info) override;

    /*** implements virtual functions inherited from application ***/       
    void run() override;
    void stop() override;

private:
    /************** dds classes **********/
    DomainParticipant* participant_;
    Subscriber* subscriber_;
    Topic* topic_;
    DataReader* reader_;
    TypeSupport type_;
  
   /********** helper variables *********/
    uint16_t received_samples_;
    std::atomic<bool> stop_;
    mutable std::mutex terminate_cv_mtx_;
    std::condition_variable terminate_cv_;
    
    /**************** data ***************/
    HelloWorld hello_;
   
    /********** helper functions **********/
    //! Return the current state of execution
    bool is_stopped();
};

} // namespace hello_world
} // namespace examples
} // namespace fastdds
} // namespace eprosima

#endif // FASTDDS_EXAMPLES_CPP_HELLO_WORLD__LISTENERSUBSCRIBERAPP_HPP
