#ifndef QM_SERVICES_MPI_APPLICATIONINSTALLER_H
#define QM_SERVICES_MPI_APPLICATIONINSTALLER_H

#include <memory>
#include <qm/models.hpp>
#include <qm/services/ApplicationInstaller.hpp>

namespace qm::services::mpi {
class MpiApplicationInstaller : public qm::services::ApplicationInstaller {
public:
    explicit MpiApplicationInstaller(std::shared_ptr<qm::services::TimeSequence> timer);
    void Install(const std::vector<std::shared_ptr<qm::models::Process>> &) override;
    void Install(const std::shared_ptr<qm::models::Process> &) override;
};
}

#endif //QM_APPLICATIONINSTALLER_H
