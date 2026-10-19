#include <iostream>
#include <cctype>

// Helper to calculate C-style string length manually
int get_length(const char arr[]) {
    int len = 0;
    while (arr[len] != '\0') {
        len++;
    }
    return len;
}

// Function to process character array in-place without auxiliary arrays
void process_char_array(char arr[], int capacity) {
    int max_len = 0;
    int max_start = -1;

    int current_len = 0;
    int current_start = -1;

    int i = 0;
    while (arr[i] != '\0') {
        if (std::isdigit(static_cast<unsigned char>(arr[i]))) {
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
        i++;
    }

    // Insert '$' before and '#' after if max digit sequence length > 3
    if (max_len > 3 && max_start != -1) {
        int total_len = get_length(arr);

        // Check buffer bounds
        if (total_len + 2 >= capacity) {
            std::cout << "Error: Array capacity too small to insert characters.\n";
            return;
        }

        // 1. Shift elements right starting from max_start to insert '$'
        for (int j = total_len; j >= max_start; --j) {
            arr[j + 1] = arr[j];
        }
        arr[max_start] = '$';
        total_len++;

        // 2. Shift elements right starting after the digit sequence to insert '#'
        int end_pos = max_start + 1 + max_len;
        for (int j = total_len; j >= end_pos; --j) {
            arr[j + 1] = arr[j];
        }
        arr[end_pos] = '#';
    }
}

int main() {
    const int CAPACITY = 256;
    char str[CAPACITY];

    std::cout << "=== Part 1: Character Array (char[]) ===\n";
    std::cout << "Enter a string: ";
    if (std::cin.getline(str, CAPACITY)) {
        process_char_array(str, CAPACITY);
        std::cout << "Processed string: " << str << "\n";
    }

    return 0;
}