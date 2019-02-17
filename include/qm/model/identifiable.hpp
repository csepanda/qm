#ifndef QM_IDENTIFIABLE_H
#define QM_IDENTIFIABLE_H

#include <string>

namespace qm::models {
class Identifiable {
    std::string m_id;
public:
    virtual std::string GetId() final {
        return m_id;
    }

    virtual void SetId(std::string id) final {
        m_id = std::move(id);
    }
};
}

#endif //QM_IDENTIFIABLE_H
