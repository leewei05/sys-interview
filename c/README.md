### Implement memcpy

1. Check if `dest` and `src` pointers are NULL. If one of them is NULL, return `dest`. This step ensures that we don't dereference `NULL` pointer, which may lead to undefined behavior.
2. `n` is type `size_t`, which is unsigned, so we need check if `n` is equal to 0. If `n` is 0, return `dest`. This check may not be necessary because we can combine this check with the for loop.
3. Cast both pointers to `unsigned char *`.
4. Construct a for loop that iterates from 0 to n - 1.
5. Copy bytes from `src` to `dest`.
6. Return `dest` at the end.

### Implement strcpy

1. Check if `dest` and `src` pointers are NULL. Return dest if one of them is NULL.
2. Iterates src until NULL terminator '\0' and copies each byte to dst.
3. Add NULL terminator after copying every byte.
4. Return `dest` at the end.
5. Add comments for users.
