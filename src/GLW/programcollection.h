/*
 * programcollection.h
 *
 *  Created on: May 10, 2020
 *      Author: timotey
 */

#ifndef GLW_MODEL_PROGRAMCOLLECTION_H_
#define GLW_MODEL_PROGRAMCOLLECTION_H_

#include "Program.h"

namespace glw
{

namespace shader
{

Program& PBR();
Program& Basic();
Program& Cubemap();
Program& Post_process();

}  // namespace shader

}  // namespace glw

#endif /* GLW_MODEL_PROGRAMCOLLECTION_H_ */
