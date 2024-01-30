#include "SoftRenderer/common.h"

bool StringUtils::EndsWith(const std::string& full_str,
                           const std::string& end_str) {
    u64 len = end_str.length();
    return full_str.size() >= len &&
           full_str.compare(full_str.size() - len, len, end_str) == 0;
}
