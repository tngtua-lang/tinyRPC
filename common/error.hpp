#pragma once
#include <sys/epoll.h>
#include <sys/errno.h>
#include <sys/socket.h>

#include <system_error>
enum class OSError {
  IO_WOULDBLOCK = EWOULDBLOCK,
  IO_AGAIN = EAGAIN,
};

struct OSErrorCategory : std::error_category {
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

inline const char* OSErrorCategory::name() const noexcept {
  return "Operating System Error";
}

enum class NetError {
  NET_NOERROR = 0,
  NET_CONN_FAILED = 1,
};

struct NetErrorCategory : std::error_category {
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

inline const char* NetErrorCategory::name() const noexcept {
  return "Net Error";
}

namespace std {
template <>
struct is_error_code_enum<OSError> : true_type {};
template <>
struct is_error_code_enum<NetError> : true_type {};
}  // namespace std

inline std::error_code make_error_code(OSError oerr) {
  return {static_cast<int>(oerr), OSErrorCategory()};
}

inline std::error_code make_error_code(NetError oerr) {
  return {static_cast<int>(oerr), NetErrorCategory()};
}
