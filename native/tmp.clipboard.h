#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  #define LIB_EXPORT __declspec(dllexport)
#else
  #define LIB_EXPORT
#endif

#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>


LIB_EXPORT int count_formats();

LIB_EXPORT char *list_available_format();

LIB_EXPORT char *get_text();

LIB_EXPORT unsigned char *get_image(size_t *loaded);

LIB_EXPORT char *get_data(const char *type);

LIB_EXPORT unsigned char *get_bytes(const char *type, size_t *loaded);

LIB_EXPORT bool clear();

LIB_EXPORT bool set_text(const char *str);

LIB_EXPORT bool set_data(const char *type, const char *str);

LIB_EXPORT bool set_image(unsigned char *data, int len);

LIB_EXPORT bool set_bytes(const char *type, unsigned char *data, int len);

#ifdef __cplusplus
}
#endif
