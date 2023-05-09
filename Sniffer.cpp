#include "Sniffer.hpp"
#include <format>

Sniffer::Sniffer(std::string virtualPortName, unsigned int deviceInPort, unsigned int deviceOutPort)
	: virtualPort{virtualPortName}, devicePort{deviceInPort, deviceOutPort}
{
	using namespace std::placeholders;

	devicePort.setCallback(std::bind(&Sniffer::inCallback, this, _1));
	virtualPort.setCallback(std::bind(&Sniffer::outCallback, this, _1));

	std::cout << "Listening.. choose MIDI device \"" << virtualPortName
		<< "\" in your software." << std::endl;
}

void Sniffer::join() {
	virtualPort.join();
	devicePort.join();
}

std::string toHex(int value) {
	return std::format("{:x}", value);
}

void Sniffer::inCallback(const std::vector<unsigned char>& data) {
	std::lock_guard<std::mutex> outGuard(outMutex);

	std::cout << "\x1B[91mDEVICE: ";
	for (int i = 0; i < data.size(); ++i) {
		std::cout << "0x" << toHex(data[i]);
		if (i != data.size() - 1)
			std::cout << ", ";
	}
	std::cout << "\033[0m\t\t" << std::endl;

	virtualPort.send(data);
}

void Sniffer::outCallback(const std::vector<unsigned char>& data) {
	std::lock_guard<std::mutex> outGuard(outMutex);

	std::cout << "\x1B[94mSOFTWARE: ";
	for (int i = 0; i < data.size(); ++i) {
		std::cout << "0x" << toHex(data[i]);
		if (i != data.size() - 1)
			std::cout << ", ";
	}
	std::cout << "\033[0m\t\t" << std::endl;

	devicePort.send(data);
}