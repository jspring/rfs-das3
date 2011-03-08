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

#ifndef SLAP_PRINTF_H_
#define SLAP_PRINTF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slapdecl.h"
#include "slaptypes.h"

/**
 * @file slap_printf.h Print Routines for cSlap Datatypes.
 * 
 * @defgroup cslap cSlap C-API 
 * @ingroup cSlap
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * <code>fprintf();</code>-function for {@link slap_UrlList}
 * 
 * @param out Output file handle
 * @param urlList The URL-list
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfUrlList(FILE * out, const slap_UrlList * urlList);

/**
 * <code>sprintf();</code>-function for {@link slap_UrlList}
 * 
 * @param str The string buffer
 * @param urlList The URL-list
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfUrlList(char * str, const slap_UrlList * urlList);

/**
 * <code>fprintf();</code>-function for {@link slap_ServerData}
 * 
 * @param out Output file handle
 * @param serverData The server-info
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfServerData(FILE * out, const slap_ServerData * serverData);

/**
 * <code>sprintf();</code>-function for {@link slap_ServerData}
 * 
 * @param str The string buffer
 * @param serverData The server-info
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfServerData(char * str, const slap_ServerData * serverData);


/**
 * <code>fprintf();</code>-function for {@link slap_DataObject}
 * 
 * @param out Output file handle
 * @param dataObj The data-object
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfDataObject(FILE * out, const slap_DataObject * dataObj);

/**
 * <code>sprintf();</code>-function for {@link slap_DataObject}
 * 
 * @param str The string buffer
 * @param dataObj The data-object element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfDataObject(char * str, const slap_DataObject * dataObj);

/**
 * <code>fprintf();</code>-function for {@link slap_DataElement}
 * 
 * @param out Output file handle
 * @param dataElem The data-element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfDataElement(FILE * out, const slap_DataElement * dataElem);

/**
 * <code>sprintf();</code>-function for {@link slap_DataElement}
 * 
 * @param str The string buffer
 * @param dataElem The data-element element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfDataElement(char * str, const slap_DataElement * dataElem);


/**
 * <code>fprintf();</code>-function for {@link slap_SetReport}
 * 
 * @param out Output file handle
 * @param dataObj The set-report 
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfSetReport(FILE * out, const slap_SetReport * setReport);

/**
 * <code>sprintf();</code>-function for {@link slap_SetReport}
 * 
 * @param str The string buffer
 * @param dataObj The set-report element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfSetReport(char * str, const slap_SetReport * setReport);

/**
 * <code>fprintf();</code>-function for {@link slap_SetReport}
 * 
 * @param out Output file handle
 * @param dataElem The set-element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfSetElement(FILE * out, const slap_SetElement * setElem);

/**
 * <code>sprintf();</code>-function for {@link slap_SetReport}
 * 
 * @param str The string buffer
 * @param dataElem The set-element element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfSetElement(char * str, const slap_SetElement * setElem);


/**
 * <code>fprintf();</code>-function for {@link slap_status_t}
 * 
 * @param out Output file handle
 * @param status The status-object
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfStatus(FILE * out, slap_status_t status);

/**
 * <code>sprintf();</code>-function for {@link slap_status_t}
 * 
 * @param str The string buffer
 * @param status The status-element element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfStatus(char * str, slap_status_t status);

/**
 * <code>fprintf();</code>-function for {@link slap_InfoObject}
 * 
 * @param out Output file handle
 * @param objInfo objInfo The object-info element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfInfoObject(FILE * out, const slap_InfoObject * objInfo);

/**
 * <code>sprintf();</code>-function for {@link slap_InfoObject}
 * 
 * @param str The string buffer
 * @param objInfo The object-info element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfInfoObject(char * str, const slap_InfoObject * objInfo);

/**
 * <code>fprintf();</code>-function for {@link slap_VapiType}
 * 
 * @param out Output file handle
 * @param typeInfo The vapi-type element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_fprintfVapiType(FILE * out, const slap_VapiType * typeInfo);

/**
 * <code>sprintf();</code>-function for {@link slap_VapiType}
 * 
 * @param str The string buffer
 * @param typeInfo The vapi-type element
 * @return Number of characters printed
 */
CSLAP_DECLARE int slap_sprintfVapiType(char * str, const slap_VapiType * typeInfo);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif /*SLAP_PRINTF_H_*/
