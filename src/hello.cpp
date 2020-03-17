#include <sys/uio.h>
#include <unistd.h>
#include <liburing.h>
#include <cstring>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <cstdint>
#include "ioring.h"
#include <experimental/coroutine>
#include "f.h"
#include <cstdio>
ioring ring;
/*
void async_pwritev2(int fd, iovec* buffers, int bufcount, int64_t offset, int flags) {
  auto sqe = ring.get_sqe();
  io_uring_prep_writev(sqe, fd, buffers, bufcount, offset);
  ring.submit();
}

f<void> async_write(int fd, const char* data) {
  iovec buffers[1] = { const_cast<void*>(reinterpret_cast<const void*>(data)), strlen(data) };
  pwritev2(fd, buffers, 1, -1, 0);
}

f<void> hi() {
  co_await async_write(1, "Hello World!\n");
}
*/

f<void> async_print(const char* str) {
  puts(str);
  co_return;
}

f<void> hi2() {
  co_await async_print("Hello!");
}

int main() {
  auto r = hi2();
}


