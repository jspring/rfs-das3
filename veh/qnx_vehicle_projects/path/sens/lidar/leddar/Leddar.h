// *****************************************************************************
// Module..: SDK -- Software development kit for Leddar products. RS-485
//           demonstration program.
//
/// \file    Leddar.h
///
/// \brief   Declarations for the Leddar layer of the demo.
///
// Copyright (c) 2013-2014 LeddarTech Inc. All rights reserved.
// Information contained herein is or may be confidential and proprietary to
// LeddarTech inc. Prior to using any part of the software development kit
// accompanying this notice, you must accept and agree to be bound to the
// terms of the LeddarTech Inc. license agreement accompanying this file.
// *****************************************************************************

#ifndef _LEDDAR_H_
#define _LEDDAR_H_

#include "OS.h"
#include <db_include.h>
#include <db_utils.h>

#define DB_LEDDAR_1_TYPE	1828
#define DB_LEDDAR_2_TYPE	1829
#define DB_LEDDAR_1_VAR		DB_LEDDAR_1_TYPE
#define DB_LEDDAR_2_VAR		DB_LEDDAR_2_TYPE

typedef struct {
	timestamp_t ts;
	float	distance[16];
	int	status;
} leddar_t;

#define LEDDAR_MAX_DETECTIONS    48
#define LEDDAR_CHANNEL_COUNT     16
#define LEDDAR_TEMPERATURE_SCALE 256.f
#define LEDDAR_EVAL_KIT          7
#define LEDDAR_IS16              8
#define LEDDAR_MODULE            9

// For LeddarConfigurationLevel
#define LEDDAR_NO_CONFIGURATION     0
#define LEDDAR_SIMPLE_CONFIGURATION 1
#define LEDDAR_FULL_CONFIGURATION   2

// Register addresses for configuration parameters
#define LEDDAR_CONFIG_ACCUMULATION   0
#define LEDDAR_CONFIG_OVERSAMPLING   1
#define LEDDAR_CONFIG_SAMPLE_COUNT   2
#define LEDDAR_CONFIG_RATE           3
#define LEDDAR_CONFIG_THRESHOLD      4
#define LEDDAR_CONFIG_LED_POWER      5
#define LEDDAR_CONFIG_OPTIONS        6 
#define LEDDAR_CONFIG_CHANGE_DELAY   7
#define LEDDAR_CONFIG_MAX_DETECTIONS 8

// Register addresses for inputs
#define LEDDAR_INPUT_TEMPERATURE 0
#define LEDDAR_INPUT_ACQ_PARAMS  13
#define LEDDAR_INPUT_TIMESTAMP   14
#define LEDDAR_INPUT_DISTANCES   16

// Bits for LEDDAR_CONFIG_OPTIONS
#define LEDDAR_OPTION_AUTO_LED  1
#define LEDDAR_OPTION_DEMERGE   4

typedef struct _LtDetection
{
    float mDistance;
    float mAmplitude;
    short mSegment;
    short mFlags;
} LtDetection;

typedef struct _LtAcquisition
{
    LtU32 mTimestamp;
    LtU16 mStates;
    LtU16 mDetectionCount;
    float mTemperature;
    
    LtDetection mDetections[LEDDAR_MAX_DETECTIONS];
} LtAcquisition;

// Bits for mStates field
#define LEDDAR_STATES_INTENSITY_MASK 0xFF
#define LEDDAR_STATES_DEMERGE_SHIFT  9

LtResult
LeddarConnect( char *aPortName, LtByte aAddress );

void
LeddarDisconnect( void );

LtBool
LeddarCanConfigure( void );

int
LeddarDeviceType( void );

LtU16
LeddarBuildNumber( void );

int
LeddarConfigurationLevel( void );

LtResult
LeddarGetResults( LtAcquisition *aAcquisition );

LtResult
LeddarGetResultsAlt( LtAcquisition *aAcquisition );

LtResult
LeddarGetTemperature( float *aValue );

LtResult
LeddarGetParameter( LtU16 aNo, LtU16 *aValue );

LtResult
LeddarSetParameter( LtU16 aNo, LtU16 aValue );

LtResult
LeddarGetThreshold( float *aValue );

LtResult
LeddarSetThreshold( float aValue );

#endif

// End of file Leddar.h
