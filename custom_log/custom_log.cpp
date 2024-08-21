#include "custom_log.h"
#include <iostream>
#include <map>
#include <ctime>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <regex>

#ifdef WIN32
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#endif

std::shared_ptr<CustomLog>	CustomLog::sTheInstance;
CustomLog& CustomLog::debug = CustomLog::GetTheInstance();


static const std::map<Level, const char*> LevelInfoStr =
{
    { Level::DEBUG, "Debug" },
    { Level::INFO, "Info" },
    { Level::WARNING, "Warning" },
    { Level::ERROR, "Error" },
    { Level::FATAL, "Fatal" },
};

std::ostream& operator<< (std::ostream& stream, const tm* tm)
{
    return stream <<std::dec<< 1900 + tm->tm_year << '-'
                  <<std::dec<< std::setfill('0') << std::setw(2) << tm->tm_mon + 1 << '-'
                  <<std::dec<< std::setfill('0') << std::setw(2) << tm->tm_mday << ' '
                  <<std::dec<< std::setfill('0') << std::setw(2) << tm->tm_hour << ':'
                  <<std::dec<< std::setfill('0') << std::setw(2) << tm->tm_min << ':'
                  <<std::dec<< std::setfill('0') << std::setw(2) << tm->tm_sec;
}


CustomLog::CustomLog()
{

}

CustomLog::~CustomLog()
{

}

CustomLog::BaseLogger CustomLog::operator()(Level level)
{
    return BaseLogger(*this,level);
}

void CustomLog::SetLevel(Level level)
{
    m_set_level_ = level;
}

const tm *CustomLog::GetLocalTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    localtime_r(&in_time_t, &m_localTime_);
    return &m_localTime_;
}

void CustomLog::endline(Level level, std::string &&message)
{
    m_lock_.lock();
    output(GetLocalTime(),level,message.c_str());
    m_lock_.unlock();
}

void CustomLog::output(const tm *p_tm, Level level, const char *str_message)
{
    if ((int)m_set_level_ > (int)level)
        return;

    std::cout << '[' << p_tm << ']'
              << '[' << LevelInfoStr.find(level)->second << "]"
              << str_message << std::endl;

    std::cout.flush();
}

void CustomLog::CreateTheInstance()
{
    sTheInstance = std::shared_ptr<CustomLog>(new CustomLog());
}
