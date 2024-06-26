#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace omp
{

    void InitializeLogs();
    void InitializeTestLogs();

}

// Categories
constexpr int LogCore = 0;
constexpr int LogRendering = 0;
constexpr int LogUI = 0;
constexpr int LogAssetManager = 0;
constexpr int LogIO = 0;
constexpr int LogTesting = 0;

// Logs
#define INFO(Category, ...) spdlog::get(#Category)->info(__VA_ARGS__)
#define WARN(Category, ...) spdlog::get(#Category)->warn(__VA_ARGS__)
#define ERROR(Category, ...) spdlog::get(#Category)->error(__VA_ARGS__)

#ifdef _MSC_VER
    #define VINFO(Category, Message, ...) spdlog::get(#Category)->info(Message, __FUNCTION__, __VA_ARGS__)
    #define VWARN(Category, Message, ...) spdlog::get(#Category)->warn(Message, __FUNCTION__, __VA_ARGS__)
    #define VERROR(Category, Message, ...) spdlog::get(#Category)->error(Message, __FUNCTION__, __VA_ARGS__)
#else
    #define VINFO(Category, Message, ...) spdlog::get(#Category)->info(Message, __FUNCTION__ __VA_OPT__(,) __VA_ARGS__)
    #define VWARN(Category, Message, ...) spdlog::get(#Category)->warn(Message, __FUNCTION__ __VA_OPT__(,) __VA_ARGS__)
    #define VERROR(Category, Message, ...) spdlog::get(#Category)->error(Message, __FUNCTION__ __VA_OPT__(,) __VA_ARGS__)
#endif
