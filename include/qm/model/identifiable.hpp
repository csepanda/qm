#ifndef QM_IDENTIFIABLE_H
#define QM_IDENTIFIABLE_H

#include <string>

namespace qm::models {
class Identifiable {
    const std::string m_id;
public:
    virtual std::string GetId() final {
        return m_id;
    }
};
}

#endif //QM_IDENTIFIABLE_H
