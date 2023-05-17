#pragma once

#include <chrono>
#include <filesystem>
#include <string>
#include <string_view>
#include <optional>
#include <functional>

#include <FA2PPCore.h>

class FileWatcher
{
public:
    enum class Status
    {
        Created,
        Deleted,
        Modified
    };

    explicit FileWatcher(
        const char* path, 
        std::chrono::milliseconds delay, 
        bool& running,
        std::optional<std::filesystem::file_time_type>& savemap_time
    );
    static void Callback(std::string path, Status status);
    void start(const std::function<void(std::string, Status)>& action);

private:

    const char* path_;
    std::filesystem::path previous_path_;
    std::chrono::milliseconds delay_;
    std::optional<std::filesystem::file_time_type> time_;
    std::optional<std::filesystem::file_time_type>& savemap_time_;
    bool& running_;
};