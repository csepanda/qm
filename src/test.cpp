#include <iostream>
#include "model.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		return 2;
	}
 
    try {
      qm::models::IPNetwork *address;
      qm::models::IPv4Network net(argv[1], argv[2]);

      address = &net;
      std::cout << "address: " << address->GetAddressStr() << std::endl;
      std::cout << "mask: " << address->GetNetmaskStr() << std::endl;
      std::cout << address->GetAddressWithMaskStr() << std::endl;
    } catch (qm::models::IPv4NetmaskFormatException& e) {
        std::cout << e.what() << std::endl;
        std::cout << e.m_source << std::endl;
    }

	return 0;
}

