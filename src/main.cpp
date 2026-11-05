#include "proc_status.hpp"
#include <iostream>
int main(int argc, char** argv) {
    std::string path = "/proc/self/status";
    if (argc > 1) path = argv[1];
    auto text = read_file(path);
    if (!text) { std::cerr << "okunamadi: " << path << "\n"; return 1; }
    auto st = ProcStatus::parse(*text);
    if (!st) { std::cerr << "ayristirilamadi\n"; return 2; }
    std::cout << "ad=" << st->name
              << " vm_rss_kb=" << st->vm_rss_kb
              << " threads=" << st->threads
              << " gonullu_anahtar=" << st->voluntary_ctxt
              << " gonulsuz_anahtar=" << st->nonvoluntary_ctxt
              << "\n";
    return 0;
}
