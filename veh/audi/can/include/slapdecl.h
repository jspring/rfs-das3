/*
 * Vehicle API - cSlap
 * Copyright (c) 2003-2008 Volkswagen Group Research.
 * All rights reserved.
 *
 * Correspondence should be directed to Volkswagen at:
 *
 * Volkswagen AG
 * Jens Krueger
 * Letter box 1777/0
 * D-38436 Wolfsburg
 * GERMANY
 *
 * email: jens2.krueger@volkswagen.de
 *
 * Neither Volkswagen Group nor the authors admit liability
 * nor provide any warranty for any of this software.
 * This material is provided "AS-IS"
 *
 * Until the distribution is granted by the Volkswagen rights
 * department this sourcecode is under non disclosure and must
 * only be used within projects with the Volkswagen group.
 */

#ifndef CSLAPDECL_H
#define CSLAPDECL_H

/*
 * Disable some warnings when compiling with VCE
 */
#if defined(WIN32) || defined(_WINDOWS)
#pragma warning (disable : 4244) /* Disable warning: 'return|argument' : conversion from '...' to '...', possible loss of data */
#pragma warning (disable : 4251) /* Disable warning: 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2' */
#pragma warning (disable : 4355) /* Disable warning: 'this' : used in base members initializer list */
#pragma warning (disable : 4267) /* Disable warning: conversion from '...' to '...', possible loss of data */
#pragma warning (disable : 4996) /* Disable warning: function was declared deprecated */
#pragma warning (disable : 4290) /* Disable warning: C++ exception specification ignored except to indicate a function is not __declspec(nothrow) */
#pragma warning (disable : 4522) /* Disable warning: multiple assignment operators specified */
#pragma warning (disable : 4101) /* Disable warning: unreferenced local variable */
#pragma warning (disable : 4200) /* Disable warning: zero-sized array in struct/union */
#pragma warning (disable : 4275) /* Disable warning: non dll-interface class 'std::_Container_base' used as base for dll-interface class 'std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,_Mfl> */

#pragma warning (disable : 4018) /* 'expression' : signed/unsigned mismatch  */

#endif


/*
 * Switch between Linux/Windows & declare the exports
 */
#if defined(DOXYGEN) || !defined(WIN32) || !defined(_WINDOWS)

#define CSLAP_DECLARE

#elif defined(cslap_EXPORTS) || defined(cxxslap_EXPORTS)

#define CSLAP_DECLARE __declspec(dllexport)

#else

#define CSLAP_DECLARE __declspec(dllimport)

#endif // defined(DOXYGEN) || !defined(WIN32) || !defined(_WINDOWS)


#endif /*CSLAPDECL_H*/
