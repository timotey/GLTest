/*
 * Buffer.cpp
 *
 *  Created on: May 13, 2020
 *      Author: timotey
 */

#include "Buffer.h"

namespace glw
{

template class Buffer<buffer_type::uniform> ;
template class Buffer<buffer_type::vertex> ;
template class Buffer<buffer_type::index> ;

} // namespace glw
