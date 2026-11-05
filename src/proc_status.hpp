#pragma once
#include <cstdint>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
struct ProcStatus {
    std::string name;
    std::int64_t vm_rss_kb = -1;
    int threads = -1;
    std::int64_t voluntary_ctxt = -1;
    std::int64_t nonvoluntary_ctxt = -1;
    static std::optional<ProcStatus> parse(std::string_view text);
};
inline std::optional<ProcStatus> ProcStatus::parse(std::string_view text) {
    ProcStatus out;
    bool any = false;
    std::string line;
    std::stringstream in{std::string(text)};
    while (std::getline(in, line)) {
        auto colon = line.find(':');
        if (colon == std::string::npos) continue;
        std::string key = line.substr(0, colon);
        std::string rest = line.substr(colon + 1);
        auto b = rest.find_first_not_of(" \t");
        if (b == std::string::npos) rest.clear();
        else rest = rest.substr(b);
        if (key == "Name") { out.name = rest; any = true; }
        else if (key == "VmRSS") { out.vm_rss_kb = std::stoll(rest); any = true; }
        else if (key == "Threads") { out.threads = std::stoi(rest); any = true; }
        else if (key == "voluntary_ctxt_switches") { out.voluntary_ctxt = std::stoll(rest); any = true; }
        else if (key == "nonvoluntary_ctxt_switches") { out.nonvoluntary_ctxt = std::stoll(rest); any = true; }
    }
    if (!any) return std::nullopt;
    return out;
}
inline std::optional<std::string> read_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) return std::nullopt;
    std::stringstream buf;
    buf << in.rdbuf();
    return buf.str();
}
