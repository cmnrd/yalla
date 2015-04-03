#include <defaultconfig.hpp>

namespace yalla
{

struct Config : public DefaultConfig
{
    static constexpr auto timer0OvfIsr = Timer0::handleOvfl;
};

}
