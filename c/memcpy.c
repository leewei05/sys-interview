#include <stddef.h>

// The memcpy() function copies n bytes from memory area src to memory area dest.
// return dest
void *memcpy(void *dest, void *src, size_t n) {
  if (!dest || !src)
    return dest;

  unsigned char *d = (unsigned char *)(dest);
  unsigned char *s = (unsigned char *)(src);
  for (size_t i = 0; i < n; i++) {
    // copy bytes
    d[i] = s[i];
  }

  return dest;
}

int main() {
  int a[3] = {1, 2, 3};
  int b[3] = {0, 0, 0};

  void *c = memcpy(&b[0], a, 3 * sizeof(int));
  int *d = (int *)(c);
  for (int i = 0; i < 3; i++) {
    if (d[i] != a[i]) {
      return 1;
    }
  }
  return 0;
}
