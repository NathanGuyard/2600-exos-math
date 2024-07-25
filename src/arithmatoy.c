#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int VERBOSE = 0;

const char *get_all_digits() { return "0123456789abcdefghijklmnopqrstuvwxyz"; }
const size_t ALL_DIGIT_COUNT = 36;

void arithmatoy_free(char *number) { free(number); }

char *arithmatoy_add(unsigned int base, const char *lhs, const char *rhs) {
    if (VERBOSE) {
        fprintf(stderr, "add %u %s %s --verbose\n", base, lhs, rhs);
    }

    if (!lhs && !rhs) return NULL;
    if (!rhs) return strdup(lhs);
    if (!lhs) return strdup(rhs);

    lhs = drop_leading_zeros(lhs);
    rhs = drop_leading_zeros(rhs);

    char *lhs_rev = reverse(strdup(lhs));
    char *rhs_rev = reverse(strdup(rhs));

    size_t lhs_len = strlen(lhs_rev);
    size_t rhs_len = strlen(rhs_rev);
    size_t max_len = lhs_len > rhs_len ? lhs_len : rhs_len;

    char *result = (char *)malloc((max_len + 2) * sizeof(char));
    if (!result) debug_abort("Memory allocation failed");

    unsigned int carry = 0;
    for (size_t i = 0; i < max_len; ++i) {
        unsigned int lhs_digit = i < lhs_len ? get_digit_value(lhs_rev[i]) : 0;
        unsigned int rhs_digit = i < rhs_len ? get_digit_value(rhs_rev[i]) : 0;
        unsigned int sum = lhs_digit + rhs_digit + carry;
        carry = sum / base;
        result[i] = to_digit(sum % base);
    }

    if (carry) result[max_len++] = to_digit(carry);
    result[max_len] = '\0';

    free(lhs_rev);
    free(rhs_rev);

    result = reverse(result);
    result = (char *)drop_leading_zeros(result);

    if (VERBOSE) {
        fprintf(stderr, "add: entering function\n");
    }

    return result;
}

char *arithmatoy_sub(unsigned int base, const char *lhs, const char *rhs) {
    if (VERBOSE) {
        fprintf(stderr, "sub %u %s %s --verbose\n", base, lhs, rhs);
    }

    if (!lhs && !rhs) return NULL;
    if (!rhs) return strdup(lhs);
    if (!lhs) return strdup(rhs);

    lhs = drop_leading_zeros(lhs);
    rhs = drop_leading_zeros(rhs);

    char *lhs_rev = reverse(strdup(lhs));
    char *rhs_rev = reverse(strdup(rhs));

    size_t lhs_len = strlen(lhs_rev);
    size_t rhs_len = strlen(rhs_rev);
    size_t max_len = lhs_len > rhs_len ? lhs_len : rhs_len;

    char *result = (char *)malloc((max_len + 1) * sizeof(char));
    if (!result) debug_abort("Memory allocation failed");

    unsigned int borrow = 0;
    for (size_t i = 0; i < max_len; ++i) {
        int lhs_digit = i < lhs_len ? get_digit_value(lhs_rev[i]) : 0;
        int rhs_digit = i < rhs_len ? get_digit_value(rhs_rev[i]) : 0;
        int diff = lhs_digit - rhs_digit - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = to_digit(diff);
    }

    result[max_len] = '\0';

    free(lhs_rev);
    free(rhs_rev);

    result = reverse(result);
    result = (char *)drop_leading_zeros(result);

    if (VERBOSE) {
        fprintf(stderr, "sub: entering function\n");
    }

    return result;
}

char *arithmatoy_mul(unsigned int base, const char *lhs, const char *rhs) {
    if (VERBOSE) {
        fprintf(stderr, "mul %u %s %s --verbose\n", base, lhs, rhs);
    }

    if (!lhs && !rhs) return NULL;
    if (!rhs) return strdup(lhs);
    if (!lhs) return strdup(rhs);

    lhs = drop_leading_zeros(lhs);
    rhs = drop_leading_zeros(rhs);

    char *lhs_rev = reverse(strdup(lhs));
    char *rhs_rev = reverse(strdup(rhs));

    size_t lhs_len = strlen(lhs_rev);
    size_t rhs_len = strlen(rhs_rev);
    size_t result_len = lhs_len + rhs_len + 1;

    char *result = (char *)calloc(result_len, sizeof(char));
    if (!result) debug_abort("Memory allocation failed");

    for (size_t i = 0; i < lhs_len; ++i) {
        unsigned int lhs_digit = get_digit_value(lhs_rev[i]);
        unsigned int carry = 0;
        for (size_t j = 0; j < rhs_len; ++j) {
            unsigned int rhs_digit = get_digit_value(rhs_rev[j]);
            unsigned int product = lhs_digit * rhs_digit + carry + get_digit_value(result[i + j]);
            carry = product / base;
            result[i + j] = to_digit(product % base);
        }
        result[i + rhs_len] = to_digit(carry);
    }

    result[result_len - 1] = '\0';

    free(lhs_rev);
    free(rhs_rev);

    result = reverse(result);
    result = (char *)drop_leading_zeros(result);

    if (VERBOSE) {
        fprintf(stderr, "mul: entering function\n");
    }

    return result;
}

unsigned int get_digit_value(char digit) {
    if (digit >= '0' && digit <= '9') {
        return digit - '0';
    }
    if (digit >= 'a' && digit <= 'z') {
        return 10 + (digit - 'a');
    }
    return -1;
}

char to_digit(unsigned int value) {
    if (value >= ALL_DIGIT_COUNT) {
        debug_abort("Invalid value for to_digit()");
        return 0;
    }
    return get_all_digits()[value];
}

char *reverse(char *str) {
    size_t len = strlen(str);
    size_t n = len / 2;
    for (size_t i = 0; i < n; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

const char *drop_leading_zeros(const char *number) {
    while (*number == '0' && *(number + 1) != '\0') {
        ++number;
    }
    return number;
}

void debug_abort(const char *debug_msg) {
    fprintf(stderr, "%s\n", debug_msg);
    exit(EXIT_FAILURE);
}
