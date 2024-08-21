#ifndef BASELOGGER_H
#define BASELOGGER_H

#include <fstream>
#include <sstream>
#include <string>

#include "custom_log.h"



class BaseLogger:public std::ostringstream
{
public:
    BaseLogger(CustomLog& custom_log,Level level);
    ~BaseLogger();


public:
    CustomLog& m_custom_log_;
    Level      m_level_;

};

#endif // BASELOGGER_H
