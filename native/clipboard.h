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


LIB_EXPORT int count_formats();

LIB_EXPORT char *list_available_format();

LIB_EXPORT char *get_text();

LIB_EXPORT unsigned char *get_image(size_t *loaded);

LIB_EXPORT char *get_data(const char *type);

LIB_EXPORT unsigned char *get_bytes(const char *type, size_t *loaded);

#ifdef __cplusplus
}
#endif
