//
// Copyright 2010 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_UHD_CONFIG_HPP
#define INCLUDED_UHD_CONFIG_HPP

// suppress warnings
#include <boost/config.hpp>
#ifdef BOOST_MSVC
# pragma warning(push)
//# pragma warning(disable: 4511) // copy constructor can't not be generated
//# pragma warning(disable: 4512) // assignment operator can't not be generated
//# pragma warning(disable: 4100) // unreferenced formal parameter 
//# pragma warning(disable: 4996) // <symbol> was declared deprecated 
//# pragma warning(disable: 4355) // 'this' : used in base member initializer list
//# pragma warning(disable: 4706) // assignment within conditional expression
# pragma warning(disable: 4251) // class 'A<T>' needs to have dll-interface to be used by clients of class 'B'
//# pragma warning(disable: 4127) // conditional expression is constant
//# pragma warning(disable: 4290) // C++ exception specification ignored except to ...
//# pragma warning(disable: 4180) // qualifier applied to function type has no meaning; ignored
# pragma warning(disable: 4275) // non dll-interface class ... used as base for dll-interface class ...
//# pragma warning(disable: 4267) // 'var' : conversion from 'size_t' to 'type', possible loss of data
//# pragma warning(disable: 4511) // 'class' : copy constructor could not be generated
#endif

//define logical operators
#ifdef BOOST_MSVC
  #define not !
  #define and &&
  #define or ||
#endif

// http://gcc.gnu.org/wiki/Visibility
// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define UHD_HELPER_DLL_IMPORT __declspec(dllimport)
  #define UHD_HELPER_DLL_EXPORT __declspec(dllexport)
  #define UHD_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define UHD_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
    #define UHD_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
    #define UHD_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define UHD_HELPER_DLL_IMPORT
    #define UHD_HELPER_DLL_EXPORT
    #define UHD_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define UHD_API and UHD_LOCAL.
// UHD_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// UHD_LOCAL is used for non-api symbols.

#define UHD_DLL // defined here, put into configuration if we need to make static libs

#ifdef UHD_DLL // defined if UHD is compiled as a DLL
  #ifdef UHD_DLL_EXPORTS // defined if we are building the UHD DLL (instead of using it)
    #define UHD_API UHD_HELPER_DLL_EXPORT
  #else
    #define UHD_API UHD_HELPER_DLL_IMPORT
  #endif // UHD_DLL_EXPORTS
  #define UHD_LOCAL UHD_HELPER_DLL_LOCAL
#else // UHD_DLL is not defined: this means UHD is a static lib.
  #define UHD_API
  #define UHD_LOCAL
#endif // UHD_DLL

#endif /* INCLUDED_UHD_CONFIG_HPP */