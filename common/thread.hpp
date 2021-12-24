//
// Created by tyx on 12/23/21.
//

#ifndef TINYRPC_THREAD_HPP
#define TINYRPC_THREAD_HPP

#include "non-copyable.h"
#include <functional>
#include <thread>
#include <sys/prctl.h>
#include <sys/syscall.h>


namespace common {
class Thread : public std::thread {
public:
  Thread() = default;

  Thread(Thread &&) = default;

  template <class F, class... Args>
  Thread(const std::string_view id, F &&f, Args &&...args)
      : std::thread(
            set, id,
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)) {}

private:
  static void set(const std::string_view name, const std::function<void()> &f) {
    if (!name.empty()) {
      ::prctl(PR_SET_NAME, name, 0, 0, 0);
    }
    f();
  }
};
} // namespace common
#endif // TINYRPC_THREAD_HPP