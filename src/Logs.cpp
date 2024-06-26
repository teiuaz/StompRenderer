#include "Logs.h"

void omp::InitializeLogs()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt"));
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    auto&& core_log = std::make_shared<spdlog::logger>("LogCore", begin(sinks), end(sinks));
    auto&& rendering_log = std::make_shared<spdlog::logger>("LogRendering", begin(sinks), end(sinks));
    auto&& ui_log = std::make_shared<spdlog::logger>("LogUI", begin(sinks), end(sinks));
    auto&& asset_log = std::make_shared<spdlog::logger>("LogAssetManager", begin(sinks), end(sinks));
    auto&& io_log = std::make_shared<spdlog::logger>("LogIO", begin(sinks), end(sinks));
    spdlog::register_logger(core_log);
    spdlog::register_logger(rendering_log);
    spdlog::register_logger(ui_log);
    spdlog::register_logger(asset_log);
    spdlog::register_logger(io_log);
    spdlog::set_pattern("[%D %H:%M:%S %z][thread %t]%^[%n][%l]%v%$");
}

void omp::InitializeTestLogs()
{
    static bool initialized = false;
    if (initialized)
    {
        return;
    }
    // TODO Log categories, not strings
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("../TestLogs.txt"));
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    auto&& core_log = std::make_shared<spdlog::logger>("LogCore", begin(sinks), end(sinks));
    auto&& rendering_log = std::make_shared<spdlog::logger>("LogRendering", begin(sinks), end(sinks));
    auto&& ui_log = std::make_shared<spdlog::logger>("LogUI", begin(sinks), end(sinks));
    auto&& asset_log = std::make_shared<spdlog::logger>("LogAssetManager", begin(sinks), end(sinks));
    auto&& io_log = std::make_shared<spdlog::logger>("LogIO", begin(sinks), end(sinks));
    auto&& test_log = std::make_shared<spdlog::logger>("LogTesting", begin(sinks), end(sinks));
    spdlog::register_logger(core_log);
    spdlog::register_logger(rendering_log);
    spdlog::register_logger(ui_log);
    spdlog::register_logger(asset_log);
    spdlog::register_logger(io_log);
    spdlog::register_logger(test_log);
    spdlog::set_pattern("[%D %H:%M:%S %z][thread %t]%^[%n][%l]%v%$");
    initialized = true;
}
