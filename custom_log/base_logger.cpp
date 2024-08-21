#include "base_logger.h"


BaseLogger::BaseLogger(CustomLog& custom_log,Level level)
                : m_custom_log_(custom_log),m_level_(level)
{

}

BaseLogger::~BaseLogger()
{

}
