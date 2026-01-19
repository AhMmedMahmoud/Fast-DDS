#ifndef FAST_DDS_GENERATED__HELLOWORLDCDRAUX_HPP
#define FAST_DDS_GENERATED__HELLOWORLDCDRAUX_HPP

#include "HelloWorld.hpp"

constexpr uint32_t HelloWorld_max_cdr_typesize {268UL};
constexpr uint32_t HelloWorld_max_key_cdr_typesize {0UL};


namespace eprosima {
namespace fastcdr {

class Cdr;
class CdrSizeCalculator;

eProsima_user_DllExport void serialize_key(
        eprosima::fastcdr::Cdr& scdr,
        const HelloWorld& data);


} // namespace fastcdr
} // namespace eprosima

#endif // FAST_DDS_GENERATED__HELLOWORLDCDRAUX_HPP

