#include <cstdio>
#include <cctype>
#include <cstring>

void process_file_string(char* str, int capacity) {
    int max_len = 0;
    int max_start = -1;

    int current_len = 0;
    int current_start = -1;

    int len = static_cast<int>(std::strlen(str));

    // Remove trailing newline character from fgets if present
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

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

    if (max_len > 3 && max_start != -1) {
        if (len + 2 >= capacity) return;

        // Shift right for '$'
        std::memmove(str + max_start + 1, str + max_start, len - max_start + 1);
        str[max_start] = '$';
        len++;

        // Shift right for '#'
        int end_pos = max_start + 1 + max_len;
        std::memmove(str + end_pos + 1, str + end_pos, len - end_pos + 1);
        str[end_pos] = '#';
    }
}

int main() {
    const int CAPACITY = 512;
    char buffer[CAPACITY];

    FILE* file1 = nullptr;
    FILE* file2 = nullptr;

#if defined(_MSC_VER)
    fopen_s(&file1, "input.txt", "r");
#else
    file1 = std::fopen("input.txt", "r");
#endif

    if (!file1) {
        std::printf("Error: Could not open input.txt for reading.\n");
        std::printf("Please create input.txt in the working directory.\n");
        return 1;
    }

    if (std::fgets(buffer, CAPACITY, file1) == nullptr) {
        std::printf("Error: Input file is empty.\n");
        std::fclose(file1);
        return 1;
    }
    std::fclose(file1);

    // Process string in-place
    process_file_string(buffer, CAPACITY);

#if defined(_MSC_VER)
    fopen_s(&file2, "output.txt", "w");
#else
    file2 = std::fopen("output.txt", "w");
#endif

    if (!file2) {
        std::printf("Error: Could not open output.txt for writing.\n");
        return 1;
    }

    std::fputs(buffer, file2);
    std::fclose(file2);

    std::printf("=== Part 3: File Processing Completed ===\n");
    std::printf("Read string from input.txt, processed, and saved to output.txt\n");

    return 0;
}