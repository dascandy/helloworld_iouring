#include <sys/uio.h>
#include <unistd.h>
#include <liburing.h>
#include <cstring>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <cstdint>
#include "ioring.h"

ioring::ioring() {
    if (io_uring_queue_init(8, &ring, 0) < 0) throw 42;
  }
io_uring_sqe* ioring::get_sqe() {
    return io_uring_get_sqe(&ring);
  }
void ioring::submit() {
    io_uring_submit(&ring);
  }

ioring::~ioring() {
    io_uring_queue_exit(&ring);
  }

