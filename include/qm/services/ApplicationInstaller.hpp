#ifndef QM_APPLICATIONINSTALLER_H
#define QM_APPLICATIONINSTALLER_H

#include <memory>
#include <qm/models.hpp>

#include "TimeSequence.h"


namespace qm::services {
class ApplicationInstaller {
    std::shared_ptr<TimeSequence> m_timer;
public:
    ApplicationInstaller(std::shared_ptr<TimeSequence>);
    void Install(const std::vector<std::shared_ptr<qm::models::Process>> &);
    void Install(const std::shared_ptr<qm::models::Process> &);
};
}

#endif //QM_APPLICATIONINSTALLER_H
