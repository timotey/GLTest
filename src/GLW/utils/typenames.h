/*
 * typenames.h
 *
 *  Created on: Feb 21, 2020
 *      Author: timotey
 */

#ifndef GLW_TYPE_TYPENAMES_H_
#define GLW_TYPE_TYPENAMES_H_

#include <math.h>

double operator "" _rad(long double in);
double operator "" _deg(long double in);
double operator "" _km(long double in);
double operator "" _m(long double in);
double operator "" _mm(long double in);

double operator "" _rad(long double in)
{
	return in;
}

double operator "" _deg(long double in)
{
	return in * 3.141593 / 180;
}

double operator "" _km(long double in)
{
	return in * 1000;
}

double operator "" _m(long double in)
{
	return in;
}

double operator "" _mm(long double in)
{
	return in / 1000;
}

#endif /* GLW_TYPE_TYPENAMES_H_ */
