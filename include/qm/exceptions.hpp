#ifndef QM_EXCEPTIONS_H
#define QM_EXCEPTIONS_H

#include <stdexcept>

namespace qm {
struct InitializationException : public std::runtime_error {
    const std::string m_source;

    explicit InitializationException(const std::string &message, std::string source) :
      std::runtime_error(message),
      m_source(std::move(source)) {
    }
};
}
#endif //QM_EXCEPTIONS_H
