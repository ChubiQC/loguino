/* Copyright 2011 David Irvine
 *
 * This file is part of Loguino
 *
 * Loguino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Loguino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Loguino.  If not, see "http://www.gnu.org/licenses/".
 *
 * $Rev$
 * $Author$
 * $Date$

*/
#include "loguino.h"

byte Logger::flushCount;

//! Sets up the logger, by calling begin on all attached loggers.
void Logger::begin()
{
    flushCount=0;


#ifdef ENABLE_SERIAL_LOGGER
    SerialLogger::begin();
#endif
#ifdef ENABLE_SD_LOGGER
    SDLogger::begin();
#endif
}


//! Sends the supplied message object to each logger attached.
//! @param msg - The Message object to log.
void Logger::log(Message &msg)
{
    if (flushCount++ > LOGGER_FLUSH_MAX){
        #ifdef ENABLE_SERIAL_OUTPUT
            debug(INFO, "Logger::log: Flush count reached, flushing SerialLogger");
            SerialLogger::flush();
        #endif
        #ifdef ENABLE_SD_OUTPUT
            debug(INFO, "Logger::log: Flush count reached, flushing SDLogger");
            SDLogger::flush();
        #endif

        flushCount=0;
    }

    #ifdef ENABLE_SERIAL_OUTPUT
        SerialLogger::log(msg);
    #endif
    #ifdef ENABLE_SD_OUTPUT
        SDLogger::log(msg);
    #endif

}



/* 
 * Initializes the poller layer, so that all subsystems can be polled
 * at a later time. 
 *
 * Iterates through each enabled poller and call the begin() method on them.
 */
void Poller::begin(){
    #ifdef ENABLE_MS_POLLER
        MSPoller::begin();
    #endif
    #ifdef ENABLE_LIS331_POLLER
        LIS331Poller::begin();
    #endif
    #ifdef ENABLE_DUMMY_POLLER
        DummyPoller::begin();
    #endif
    #ifdef ENABLE_GPS_POLLER
        GPSPoller::begin();
    #endif
    #ifdef ENABLE_DIGITAL_POLLER
        DigitalPoller::begin();
    #endif
    #ifdef ENABLE_ANALOG_POLLER
        AnalogPoller::begin();
    #endif
    #ifdef ENABLE_ITG3200_POLLER
        ITG3200Poller::begin();
    #endif
}


/**
 * Responsible for polling all connected hardware and generating log messages.
 * 
 * Iterates through each enabled poller, and calls the poll() method.
 */
void Poller::poll()
{
    #ifdef ENABLE_MS_POLLER
        MSPoller::poll();
    #endif
    #ifdef ENABLE_LIS331_POLLER
        LIS331Poller::poll();
    #endif
    #ifdef ENABLE_DUMMY_POLLER
        DummyPoller::poll();
    #endif
    #ifdef ENABLE_GPS_POLLER
        GPSPoller::poll();
    #endif
    #ifdef ENABLE_DIGITAL_POLLER
        DigitalPoller::poll();
    #endif
    #ifdef ENABLE_ANALOG_POLLER
        AnalogPoller::poll();
    #endif
    #ifdef ENABLE_ITG3200_POLLER
        ITG3200Poller::poll();
    #endif
}

