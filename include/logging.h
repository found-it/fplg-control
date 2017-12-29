/*****************************************************
 *
 *  File:   logging.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */

#ifndef LOGGER_H
#define LOGGER_H

#define RED     "\033[1;31m"
#define PURPLE  "\033[1;35m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
void logr(char *fmt, ...);

/*
#define __SHORT_FILE__
*/

/* TODO: ADD TYPE */
#define __LPEC_LOG__(format, ...) logr("[%s] [%s:%d] " format, __func__, __FILE__, __LINE__, ## __VA_ARGS__)
#define LOG_ERR(format, ...)__LPEC_LOG__(format, ## __VA_ARGS__)

#define LOG_ERROR(fmt, ...) do { fprintf(stdout, RED    "[ERROR]   [%s:%d] [%s]: " fmt, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#define LOG_WARN(fmt, ...)  do { fprintf(stdout, YELLOW "[WARNING] [%s:%d] [%s]: " fmt, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#define LOG_DEBUG(fmt, ...) do { fprintf(stdout, PURPLE "[DEBUG]   [%s:%d] [%s]: " fmt, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#define LOG_INFO(fmt, ...)  do { fprintf(stdout, GREEN  "[INFO]    [%s:%d] [%s]: " fmt, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)

#endif

