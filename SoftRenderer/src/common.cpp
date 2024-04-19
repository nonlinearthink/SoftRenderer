#include "SoftRenderer/common.h"

#include <sstream>

bool StringUtils::EndsWith(const std::string &full_str,
                           const std::string &end_str) {
    u64 len = end_str.length();
    return full_str.size() >= len &&
           full_str.compare(full_str.size() - len, len, end_str) == 0;
}

std::string StringUtils::Format(
    const std::string &fmt_str,
    const std::initializer_list<const char *> &args) {
    std::ostringstream oss;
    size_t arg_index = 0;
    for (size_t i = 0; i < fmt_str.size(); ++i) {
        if (fmt_str[i] == '{' && i + 1 < fmt_str.size() &&
            fmt_str[i + 1] == '}') {
            if (arg_index < args.size()) {
                oss << args.begin()[arg_index];
                ++arg_index;
            }
            ++i;  // Skip the closing brace.
        } else {
            oss << fmt_str[i];
        }
    }
    return oss.str();
}
