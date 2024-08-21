/*
*File - custom_log.h
*
*this file is part of the Inuitive test
*
*/

#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <memory>


#ifdef _MSC_VER
#define __FILENAME__ (strrchr(__FILE__, '\\') + 1)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') + 1)
#endif

#define LOG_DEBUG CustomLog::debug(Level::DEBUG) << "["<<__FILENAME__<<"-"<<__LINE__<<"-"<<__FUNCTION__<<"]\t"

#define LOG_INFO CustomLog::debug(Level::INFO) << "["<<__FILENAME__<<"-"<<__LINE__<<"-"<<__FUNCTION__<<"]\t"

#define LOG_WARNING CustomLog::debug(Level::WARNING) << "["<<__FILENAME__<<"-"<<__LINE__<<"-"<<__FUNCTION__<<"]\t"

#define LOG_ERROR CustomLog::debug(Level::ERROR) << "["<<__FILENAME__<<"-"<<__LINE__<<"-"<<__FUNCTION__<<"]\t"



//level ERROR > WARNING > INFO > DEBUG
enum Level {
    DEBUG,      ///< 打印所有级别日志,打印高于DEBUG(包含)级别日志
    INFO,       ///< 打印高于INFO(包含)级别日志
    WARNING,    ///< 打印高于WARNING(包含)级别日志
    ERROR,      ///< 打印高于ERROR(包含)级别日志
    FATAL       ///< 关闭
};

class CustomLog
{
public:
    class BaseLogger:public std::ostringstream
    {
        public:
            BaseLogger(CustomLog& custom_log,Level level): m_custom_log_(custom_log),m_level_(level){};
            ~BaseLogger()
            {
                m_custom_log_.endline(m_level_,std::move(str()));
            }

        public:
            CustomLog& m_custom_log_;
            Level      m_level_;
    };

public:
    CustomLog();
    ~CustomLog();

    BaseLogger operator()(Level level = Level::DEBUG);

    void SetLevel(Level level);

private:
    const tm* GetLocalTime();

    void endline(Level level, std::string&& message);

    void output(const tm* p_tm,
                    Level level,
                    const char* str_message);
private:
    std::mutex m_lock_;
    tm m_localTime_;
    Level m_set_level_ = Level::INFO;

    static std::shared_ptr<CustomLog>	sTheInstance;
    static void   CreateTheInstance();

public:
    static CustomLog &debug;
    static CustomLog& GetTheInstance();
};

inline CustomLog& CustomLog::GetTheInstance()
{
    //Hold a reference to the static instance.
    if (sTheInstance == nullptr)
    {
        CreateTheInstance();
    }
    return *sTheInstance;
}
