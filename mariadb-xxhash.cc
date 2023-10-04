#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <xxhash.h>

extern "C" {
    my_bool xxhash64_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
    void xxhash64_deinit(UDF_INIT *initid);
    long long xxhash64(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

    my_bool xxhash32_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
    void xxhash32_deinit(UDF_INIT *initid);
    long long xxhash32(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

    my_bool xxhash32s_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
    void xxhash32s_deinit(UDF_INIT *initid);
    long long xxhash32s(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
}

my_bool xxhash64_init(UDF_INIT* initid, UDF_ARGS* args, char* message) {
    if(args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
        strcpy(message, "xxhash64() requires one string argument");
        return 1;
    }
    initid->maybe_null = 0;
    initid->const_item = 1;
    return 0;
}

long long xxhash64(UDF_INIT* initid, UDF_ARGS* args, char* is_null, char* error) {
    const char *s = args->args[0];
    size_t length = (s != NULL) ? args->lengths[0] : 0;
    return XXH64(s, length, 0);
}

void xxhash64_deinit(UDF_INIT *initid) {
}

my_bool xxhash32_init(UDF_INIT* initid, UDF_ARGS* args, char* message) {
    if(args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
        strcpy(message, "xxhash32() requires one string argument");
        return 1;
    }
    initid->maybe_null = 0;
    initid->const_item = 1;
    return 0;
}

long long xxhash32(UDF_INIT* initid, UDF_ARGS* args, char* is_null, char* error) {
    const char *s = args->args[0];
    size_t length = (s != NULL) ? args->lengths[0] : 0;
    return XXH32(s, length, 0);
}

void xxhash32_deinit(UDF_INIT *initid) {
}

my_bool xxhash32s_init(UDF_INIT* initid, UDF_ARGS* args, char* message) {
    if(args->arg_count != 1 || args->arg_type[0] != STRING_RESULT) {
        strcpy(message, "xxhash32s() requires one string argument");
        return 1;
    }
    initid->maybe_null = 0;
    initid->const_item = 1;
    return 0;
}

long long xxhash32s(UDF_INIT* initid, UDF_ARGS* args, char* is_null, char* error) {
    const char *s = args->args[0];
    size_t length = (s != NULL) ? args->lengths[0] : 0;
    long long result = XXH32(s, length, 0);
    return result > 0x7FFFFFFF ? (result - 0x100000000) : result;
}

void xxhash32s_deinit(UDF_INIT *initid) {
}
