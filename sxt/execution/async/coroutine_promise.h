#pragma once

#include <concepts>
#include <coroutine>
#include <utility>

#include "sxt/base/error/panic.h"
#include "sxt/execution/async/future.h"
#include "sxt/execution/async/promise.h"
#include "sxt/execution/async/task.h"

namespace sxt::xena {
//--------------------------------------------------------------------------------------------------
// coroutine_promise_impl
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class T, class Promise> class coroutine_promise_impl : public task {
public:
  coroutine_promise_impl() noexcept = default;
  coroutine_promise_impl(const coroutine_promise_impl&) = delete;
  coroutine_promise_impl(coroutine_promise_impl&&) = delete;

  coroutine_promise_impl& operator=(const coroutine_promise_impl&) = delete;
  coroutine_promise_impl& operator=(coroutine_promise_impl&&) = delete;

  std::suspend_never initial_suspend() const noexcept { return {}; }
  std::suspend_never final_suspend() const noexcept { return {}; }

  void unhandled_exception() noexcept { baser::panic("we don't support exceptions in coroutines"); }

  future<T> get_return_object() noexcept { return future<T>{promise_}; }

  // task
  void run_and_dispose() noexcept override {
    auto handle = std::coroutine_handle<Promise>::from_promise(static_cast<Promise&>(*this));
    handle.resume();
  }

protected:
  promise<T> promise_;
};
} // namespace detail

//--------------------------------------------------------------------------------------------------
// coroutine_promise
//--------------------------------------------------------------------------------------------------
template <class T>
class coroutine_promise final : public detail::coroutine_promise_impl<T, coroutine_promise<T>> {
public:
  template <class... Args>
    requires std::constructible_from<T, Args&&...>
  void return_value(Args&&... args) noexcept {
    this->promise_.set_value(std::forward<Args>(args)...);
  }
};

template <>
class coroutine_promise<void> final
    : public detail::coroutine_promise_impl<void, coroutine_promise<void>> {
public:
  void return_void() noexcept { this->promise_.make_ready(); }
};

extern template class coroutine_promise<void>;
} // namespace sxt::xena
