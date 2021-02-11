#ifndef NEW_LOGGING_H_
#define NEW_LOGGING_H_

#include <sys/time.h>

#include <chrono>
#include <csignal>
#include <functional>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

namespace arl
{
namespace timing
{
inline int64_t& _Var_start_seconds()
{
    static int64_t start_seconds;
    return start_seconds;
}

inline int64_t& _Var_stop_seconds()
{
    static int64_t stop_seconds;
    return stop_seconds;
}

inline int64_t& _Var_start_micro_seconds()
{
    static int64_t start_micro_seconds;
    return start_micro_seconds;
}

inline int64_t& _Var_stop_micro_seconds()
{
    static int64_t stop_micro_seconds;
    return stop_micro_seconds;
}

inline void startTimer()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    _Var_start_seconds() = current_time.tv_sec;
    _Var_start_micro_seconds() = current_time.tv_usec;
}

inline void stopTimer()
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    _Var_stop_seconds() = current_time.tv_sec;
    _Var_stop_micro_seconds() = current_time.tv_usec;
}

}  // namespace timing

namespace logging
{
namespace internal
{
enum class MessageSeverity
{
    LOG,
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    TRACE,
    FATAL,
    ASSERTION,
    EXIT
};

// Helper functions
inline std::string getSeverityColor(const MessageSeverity msg_severity)
{
    std::string severity_string;
    switch (msg_severity)
    {
        case MessageSeverity::LOG:
            severity_string = "\033[0m";
            break;
        case MessageSeverity::INFO:
            severity_string = "\033[32m";
            break;
        case MessageSeverity::DEBUG:
            severity_string = "\033[36m";
            break;
        case MessageSeverity::WARNING:
            severity_string = "\033[33m";
            break;
        case MessageSeverity::TRACE:
            severity_string = "\033[34m";
            break;
        case MessageSeverity::ERROR:
            severity_string = "\033[31m";
            break;
        case MessageSeverity::FATAL:
            severity_string = "\033[31m";
            break;
        case MessageSeverity::ASSERTION:
            severity_string = "\033[31m";
            break;
        case MessageSeverity::EXIT:
            severity_string = "\033[31m";
            break;
        default:
            severity_string = "UNKNOWNSEVERITYCOLOR";
    }
    return severity_string;
}

inline std::string getSeverityString(const MessageSeverity msg_severity)
{
    std::string severity_string;
    switch (msg_severity)
    {
        case MessageSeverity::LOG:
            severity_string = "LOG";
            break;
        case MessageSeverity::INFO:
            severity_string = "INFO";
            break;
        case MessageSeverity::DEBUG:
            severity_string = "DEBUG";
            break;
        case MessageSeverity::WARNING:
            severity_string = "WARNING";
            break;
        case MessageSeverity::TRACE:
            severity_string = "TRACE";
            break;
        case MessageSeverity::ERROR:
            severity_string = "ERROR";
            break;
        case MessageSeverity::FATAL:
            severity_string = "FATAL";
            break;
        case MessageSeverity::ASSERTION:
            severity_string = "ASSERTION FAILED";
            break;
        case MessageSeverity::EXIT:
            severity_string = "EXIT";
            break;
        default:
            severity_string = "UNKNOWNSEVERITY";
    }
    return severity_string;
}

inline std::string getWhiteColorString()
{
    return "\033[0m";
}

inline std::string decNumberAsHexString(const size_t dec_number)
{
    std::stringstream str_stream;
    str_stream << std::hex << dec_number;
    return str_stream.str();
}

inline size_t getThreadId()
{
    return std::hash<std::thread::id>{}(std::this_thread::get_id());
}

inline std::string loggingGetTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char time_c_str[100];
    sprintf(time_c_str,
            "%d_%02d_%02d__%02d_%02d_%02d",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);
    const std::string time_str(time_c_str);
    return time_str;
}

// Global variables

inline std::mutex& _Var_thread_mutex()
{
    static std::mutex mtx;
    return mtx;
}

inline bool& _Var_use_colors()
{
    static bool use_colors = true;
    return use_colors;
}

inline bool& _Var_show_file()
{
    static bool show_file = true;
    return show_file;
}

inline bool& _Var_show_func()
{
    static bool show_func = true;
    return show_func;
}

inline bool& _Var_show_line_number()
{
    static bool show_line_number = true;
    return show_line_number;
}

inline bool& _Var_show_thread_id()
{
    static bool thread_id = true;
    return thread_id;
}

// Set get for global variables

inline bool getUseColors()
{
    const bool use_colors = _Var_use_colors();
    return use_colors;
}

inline void setUseColors(const bool new_val)
{
    std::lock_guard<std::mutex> guard(_Var_thread_mutex());
    _Var_use_colors() = new_val;
}

inline bool getShowFunc()
{
    const bool show_func = _Var_show_func();
    return show_func;
}

inline void setShowFunc(const bool new_val)
{
    std::lock_guard<std::mutex> guard(_Var_thread_mutex());
    _Var_show_func() = new_val;
}

inline bool getShowFile()
{
    const bool show_file = _Var_show_file();
    return show_file;
}

inline void setShowFile(const bool new_val)
{
    std::lock_guard<std::mutex> guard(_Var_thread_mutex());
    _Var_show_file() = new_val;
}

inline bool getShowLineNumber()
{
    const bool show_line_number = _Var_show_line_number();
    return show_line_number;
}

inline void setShowLineNumber(const bool new_val)
{
    std::lock_guard<std::mutex> guard(_Var_thread_mutex());
    _Var_show_line_number() = new_val;
}

inline bool getShowThreadId()
{
    const bool show_thread_id = _Var_show_thread_id();
    return show_thread_id;
}

inline void setShowThreadId(const bool new_val)
{
    std::lock_guard<std::mutex> guard(_Var_thread_mutex());
    _Var_show_thread_id() = new_val;
}

inline std::string getPreString(const MessageSeverity msg_severity,
                                const char* file_name,
                                const char* func_name,
                                const int line_number)
{
    const std::string severity_color = getUseColors() ? getSeverityColor(msg_severity) : "";
    const std::string reset_color = getUseColors() ? getWhiteColorString() : "";

    const std::string file_name_string = std::string(file_name);
    const std::string file_name_no_path =
        file_name_string.substr(file_name_string.find_last_of("/") + 1);

    const std::string func_string = getShowFunc() ? "[ " + std::string(func_name) + " ]" : "";

    const std::string file_string = getShowFile() ? "[ " + file_name_no_path + " ]" : "";
    const std::string line_number_string =
        getShowLineNumber() ? "[ " + std::to_string(line_number) + " ]" : "";
    const std::string severity_string = "[ " + getSeverityString(msg_severity) + " ]";
    const std::string thread_id_string =
        getShowThreadId() ? "[ 0x" + decNumberAsHexString(getThreadId()) + " ]" : "";
    const std::string time_string = "[ " + loggingGetTime() + " ]";
    return severity_color + severity_string + time_string + thread_id_string + file_string +
           func_string + line_number_string + ": " + reset_color;
}

class Log
{
public:
    explicit Log(const MessageSeverity msg_severity,
                 const char* file_name,
                 const char* func_name,
                 const int line_number)
        : pre_string_(getPreString(msg_severity, file_name, func_name, line_number)),
          assertion_condition_(true),
          should_print_(true)
    {
    }

    explicit Log(const MessageSeverity msg_severity,
                 const char* file_name,
                 const char* func_name,
                 const int line_number,
                 const bool cond)
        : pre_string_(getPreString(msg_severity, file_name, func_name, line_number)),
          assertion_condition_(cond),
          should_print_(false)
    {
    }

    explicit Log() : pre_string_(""), assertion_condition_(true), should_print_(true) {}

    explicit Log(const bool cond) : pre_string_(""), assertion_condition_(true), should_print_(cond)
    {
    }

    std::ostringstream& getStream()
    {
        return string_stream_;
    }

    ~Log()
    {
        if (!assertion_condition_)
        {
            std::cout << pre_string_ + string_stream_.str() << std::endl;
            raise(SIGABRT);
        }
        else
        {
            if (should_print_)
            {
                std::cout << pre_string_ + string_stream_.str() << std::endl;
            }
        }
    }

private:
    std::ostringstream string_stream_;
    const std::string pre_string_;
    const bool assertion_condition_;
    const bool should_print_;
};

}  // namespace internal

inline void useColors(const bool use_colors)
{
    arl::logging::internal::setUseColors(use_colors);
}

inline void showFile(const bool show_file)
{
    arl::logging::internal::setShowFile(show_file);
}

inline void showLineNumber(const bool show_line_number)
{
    arl::logging::internal::setShowLineNumber(show_line_number);
}

inline void showFunction(const bool show_function)
{
    arl::logging::internal::setShowFunc(show_function);
}

inline void showThreadId(const bool show_thread_id)
{
    arl::logging::internal::setShowThreadId(show_thread_id);
}

}  // namespace logging
}  // namespace arl

#define LOG()                                                                       \
    arl::logging::internal::Log(                                                    \
        arl::logging::internal::MessageSeverity::LOG, __FILE__, __func__, __LINE__) \
        .getStream()
#define LOG_INFO()                                                                   \
    arl::logging::internal::Log(                                                     \
        arl::logging::internal::MessageSeverity::INFO, __FILE__, __func__, __LINE__) \
        .getStream()
#define LOG_DEBUG()                                                                   \
    arl::logging::internal::Log(                                                      \
        arl::logging::internal::MessageSeverity::DEBUG, __FILE__, __func__, __LINE__) \
        .getStream()
#define LOG_WARNING()                                                                   \
    arl::logging::internal::Log(                                                        \
        arl::logging::internal::MessageSeverity::WARNING, __FILE__, __func__, __LINE__) \
        .getStream()
#define LOG_TRACE()                                                                   \
    arl::logging::internal::Log(                                                      \
        arl::logging::internal::MessageSeverity::TRACE, __FILE__, __func__, __LINE__) \
        .getStream()
#define LOG_ERROR()                                                                   \
    arl::logging::internal::Log(                                                      \
        arl::logging::internal::MessageSeverity::ERROR, __FILE__, __func__, __LINE__) \
        .getStream()
#define LOG_FATAL()                                                                   \
    arl::logging::internal::Log(                                                      \
        arl::logging::internal::MessageSeverity::FATAL, __FILE__, __func__, __LINE__) \
        .getStream()

#define PRINT() arl::logging::internal::Log().getStream()

#define PRINT_COND(cond) arl::logging::internal::Log(cond).getStream()

#define ASSERT(cond)                                                                            \
    arl::logging::internal::Log(                                                                \
        arl::logging::internal::MessageSeverity::ASSERTION, __FILE__, __func__, __LINE__, cond) \
        .getStream()

#define EXIT(cond)                                                                          \
    arl::logging::internal::Log(                                                            \
        arl::logging::internal::MessageSeverity::EXIT, __FILE__, __func__, __LINE__, false) \
        .getStream()

#define TIC() arl::timing::startTimer()

#define TOC_MS(msg)                                                                           \
    {                                                                                         \
        arl::timing::stopTimer();                                                             \
        int64_t delta_seconds =                                                               \
            arl::timing::_Var_stop_seconds() - arl::timing::_Var_start_seconds();             \
        int64_t delta_microseconds =                                                          \
            arl::timing::_Var_stop_micro_seconds() - arl::timing::_Var_start_micro_seconds(); \
        int64_t delta_time = delta_seconds * 1000000 + delta_microseconds;                    \
        LOG_DEBUG() << msg << static_cast<float>(delta_time) / 1000.0f << " ms";              \
    }

#define TOC_US(msg)                                                                           \
    {                                                                                         \
        arl::timing::stopTimer();                                                             \
        int64_t delta_seconds =                                                               \
            arl::timing::_Var_stop_seconds() - arl::timing::_Var_start_seconds();             \
        int64_t delta_microseconds =                                                          \
            arl::timing::_Var_stop_micro_seconds() - arl::timing::_Var_start_micro_seconds(); \
        int64_t delta_time = delta_seconds * 1000000 + delta_microseconds;                    \
        LOG_DEBUG() << msg << delta_time << " us";                                            \
    }

#endif
