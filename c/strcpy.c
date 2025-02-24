#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Caller must ensure dst has enough space for src including the null terminator.
// Return a pointer to char where it holds the copied characters from src.
char *my_strcpy(char *dst, const char *src) {
  // bail if either pointer is NULL
  if (!dst || !src)
    return dst;

  int i = 0;
  for (; src[i]; i++) {
    dst[i] = src[i];
  }

  // Cap it off with a null terminator
  dst[i] = '\0';

  return dst;
}

// pointer-based implementation
char *my_strcpy2(char *dst, const char *src) {
  if (!dst || !src)
    return dst;

  char *head = dst;
  while(*src) {
    *dst++ = *src++;
  }

  *dst = '\0';

  return head;
}

int main() {
  char *s = "hello world!";
  printf("src: %s\n", s);

  char *d = (char *)malloc(sizeof(char) * (strlen(s) + 1));
  // d = my_strcpy(d, s);
  d = my_strcpy2(d, s);
  printf("dst: %s\n", d);

  return 0;
}
