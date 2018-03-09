/*****************************************************
 *
 *  File:   logging.h
 *  Author: James Petersen <jpetersenames@gmail.com>
 *
 *****************************************************
 */

#ifndef LOGGING_H
#define LOGGING_H

#define RED     "\033[1;31m"
#define PURPLE  "\033[1;35m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[1;0m"
void logr(char *fmt, ...);

/*
#define __SHORT_FILE__
*/

#define LOG_ERROR(fmt, ...) do { fprintf(stdout, RED    "[ERROR]   [%s:%d] [%s]: " fmt RESET, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#define LOG_WARN(fmt, ...)  do { fprintf(stdout, YELLOW "[WARNING] [%s:%d] [%s]: " fmt RESET, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#define LOG_DEBUG(fmt, ...) do { fprintf(stdout, PURPLE "[DEBUG]   [%s:%d] [%s]: " fmt RESET, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)
#define LOG_INFO(fmt, ...)  do { fprintf(stdout, GREEN  "[INFO]    [%s:%d] [%s]: " fmt RESET, __FILE__,  __LINE__, __func__, __VA_ARGS__); } while (0)

#define LOG_ERROR_S(fmt) LOG_ERROR("%s", fmt)
#define LOG_WARN_S(fmt)  LOG_WARN("%s", fmt)
#define LOG_DEBUG_S(fmt) LOG_DEBUG("%s", fmt)
#define LOG_INFO_S(fmt)  LOG_INFO("%s", fmt)
#endif

