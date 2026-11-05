#include "proc_status.hpp"
#include <iostream>
static int fails;
#define CHECK(c) do { if (!(c)) { std::cerr << "fail " << __LINE__ << " " << #c << "\n"; fails++; } } while (0)
int main() {
    const char* sample =
        "Name:\tprocspine-test\n"
        "VmRSS:\t  1234 kB\n"
        "Threads:\t2\n"
        "voluntary_ctxt_switches:\t10\n"
        "nonvoluntary_ctxt_switches:\t3\n";
    auto st = ProcStatus::parse(sample);
    CHECK(st.has_value());
    CHECK(st->name == "procspine-test");
    CHECK(st->vm_rss_kb == 1234);
    CHECK(st->threads == 2);
    CHECK(st->voluntary_ctxt == 10);
    CHECK(st->nonvoluntary_ctxt == 3);
    CHECK(!ProcStatus::parse("bogus\n").has_value());
    auto live = read_file("/proc/self/status");
    if (live) {
        auto self = ProcStatus::parse(*live);
        CHECK(self.has_value());
        CHECK(self->threads >= 1);
        CHECK(self->voluntary_ctxt >= 0);
    }
    if (fails) return 1;
    std::cout << "ok\n";
    return 0;
}
