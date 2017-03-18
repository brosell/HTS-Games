// required by boost since we are exceptionless
#include "boost/shared_ptr.hpp"
inline void boost::throw_exception(std::exception const & e)
{
}

