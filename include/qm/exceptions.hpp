#ifndef QM_EXCEPTIONS_H
#define QM_EXCEPTIONS_H

#include <stdexcept>

namespace qm {
struct ParseException : public std::runtime_error {
    const std::string m_source;

    explicit ParseException(const std::string &message, std::string source) :
      std::runtime_error(message),
      m_source(std::move(source)) {
    }
};

struct InitializationException : public std::runtime_error {
    const std::string m_source;

    explicit InitializationException(const std::string &message, std::string source) :
      std::runtime_error(message),
      m_source(std::move(source)) {
    }
};

struct UninitializedException : public std::runtime_error {
    explicit UninitializedException(const std::string &message) : std::runtime_error(message) { }
};
}
#endif //QM_EXCEPTIONS_H
