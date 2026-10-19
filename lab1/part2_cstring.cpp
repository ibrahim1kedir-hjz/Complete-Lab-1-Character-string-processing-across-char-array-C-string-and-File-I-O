#include <iostream>
#include <cstring>
#include <cctype>

void process_cstring(char* str, int capacity) {
    if (str == nullptr) return;

    int max_len = 0;
    int max_start = -1;

    int current_len = 0;
    int current_start = -1;

    int len = static_cast<int>(std::strlen(str));

    for (int i = 0; i < len; ++i) {
        if (std::isdigit(static_cast<unsigned char>(str[i]))) {
            if (current_len == 0) {
                current_start = i;
            }
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
                max_start = current_start;
            }
        }
        else {
            current_len = 0;
        }
    }

    // Insert '$' and '#' in-place using memmove
    if (max_len > 3 && max_start != -1) {
        if (len + 2 >= capacity) {
            std::cout << "Error: C-string buffer capacity exceeded.\n";
            return;
        }

        // Shift right by 1 position at max_start for '$'
        std::memmove(str + max_start + 1, str + max_start, len - max_start + 1);
        str[max_start] = '$';
        len++;

        // Shift right by 1 position at end_pos for '#'
        int end_pos = max_start + 1 + max_len;
        std::memmove(str + end_pos + 1, str + end_pos, len - end_pos + 1);
        str[end_pos] = '#';
    }
}

int main() {
    const int CAPACITY = 256;
    char str[CAPACITY];

    std::cout << "=== Part 2: C-Style String (Null-Terminated) ===\n";
    std::cout << "Enter a string: ";
    if (std::cin.getline(str, CAPACITY)) {
        process_cstring(str, CAPACITY);
        std::cout << "Result C-string: " << str << "\n";
    }

    return 0;
}