#ifdef __APPLE__

#include <iostream>

int main() { return 0; }

#else

#include <iostream>

int main() {
    std::cout << "Unsupported operating systems." << std::endl;
    return 0;
}

#endif
