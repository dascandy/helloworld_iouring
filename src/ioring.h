#pragma once

#include <liburing.h>

struct ioring {
	struct io_uring ring;
  uint16_t pendingSubmit, pendingComplete;
  ioring();
  io_uring_sqe* get_sqe();
  void submit();
  ~ioring();
};


