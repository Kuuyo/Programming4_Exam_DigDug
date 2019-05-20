#ifndef PCH_H
#define PCH_H

#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "Log.h" // Various logging functions

// https://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type
template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type
{
	return static_cast<typename std::underlying_type<E>::type>(e);
}
#endif //PCH_H