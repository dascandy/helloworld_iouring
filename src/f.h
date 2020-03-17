#pragma once

#include <experimental/coroutine>

template <typename T>
struct f {
  bool await_ready() const noexcept { return false; }
  void await_suspend(std::experimental::coroutine_handle<> awaitingCoroutine) noexcept {
    this->awaitingCoroutine = awaitingCoroutine;
  }
  auto await_resume() const { return std::move(value); }
private:
  std::experimental::coroutine_handle<> awaitingCoroutine;
  T value;
};

template <>
struct f<void> {
  bool await_ready() const noexcept { return false; }
  void await_suspend(std::experimental::coroutine_handle<> awaitingCoroutine) noexcept {
    this->awaitingCoroutine = awaitingCoroutine;
  }
  void await_resume() noexcept {}
private:
  std::experimental::coroutine_handle<> awaitingCoroutine;
};

template <typename R, typename... Args>
struct std::experimental::coroutine_traits<f<R>, Args...>
{
  struct promise_type
  {
    f<R> p;
    auto& get_return_object()
    {
      return p;
    }
    std::experimental::suspend_always initial_suspend()
    {
      return {};
    }
    std::experimental::suspend_never final_suspend()
    {
      return {};
    }
    template <typename U>
    void return_value(U&& u)
    {
      p.value = std::forward<decltype(u)>(u);
    }
    void unhandled_exception()
    {
    }
  };
};

template <typename... Args>
struct std::experimental::coroutine_traits<f<void>, Args...>
{
  struct promise_type
  {
    f<void> p;
    auto& get_return_object()
    {
      return p;
    }
    std::experimental::suspend_always initial_suspend()
    {
      return {};
    }
    std::experimental::suspend_never final_suspend()
    {
      return {};
    }
    void return_void()
    {
    }
    void unhandled_exception()
    {
    }
  };
};

