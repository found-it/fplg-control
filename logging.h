/***************************************************
 *
 *  File:   logging.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 ***************************************************
 */

#ifndef LOGGER_H
#define LOGGER_H

#define LOG_COLOR_RED   "\033[0;31m"

/*
#define __SHORT_FILE__
*/

void logr(char *fmt, ...);

/* TODO: ADD TYPE */
#define __LPEC_LOG__(format, ...) logr("[%s] [%s:%d] " format, __func__, __FILE__, __LINE__, ## __VA_ARGS__)
#define LOG_ERROR(format, ...)__LPEC_LOG__(format, ## __VA_ARGS__)

#define PERR(fmt, ...)\
    do { fprintf(stdout, LOG_COLOR_RED "[%s] [%s:%d]: " fmt, __FILE__, \
            __func__, __LINE__, __VA_ARGS__); } while (0)

#endif

