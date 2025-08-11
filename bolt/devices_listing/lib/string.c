#include "../include/kernel.h"

// String length
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) {
        len++;
    }
    return len;
}

// String comparison
int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

// Memory set
void* memset(void* ptr, int value, size_t size) {
    unsigned char* p = (unsigned char*)ptr;
    while (size--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

// Memory copy
void* memcpy(void* dest, const void* src, size_t size) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    while (size--) {
        *d++ = *s++;
    }
    return dest;
}

// String copy
char* strcpy(char* dest, const char* src) {
    char* original_dest = dest;
    while ((*dest++ = *src++));
    return original_dest;
}

// String concatenation
char* strcat(char* dest, const char* src) {
    char* original_dest = dest;
    while (*dest) dest++;  // Find end of dest
    while ((*dest++ = *src++));  // Copy src to end of dest
    return original_dest;
}