#include "VirtualMidiPort.hpp"
#include <iostream>

VirtualMidiPort::VirtualMidiPort(std::string name) {
#ifdef _WIN32
	std::wstring s(name.begin(), name.end());
	port = virtualMIDICreatePortEx2(s.c_str(), NULL, NULL, 65535, TE_VM_FLAGS_PARSE_RX);
	buffer = new unsigned char[65535];
#else
	inPort.openVirtualPort(name);
	outPort.openVirtualPort(name);
#endif
}

VirtualMidiPort::~VirtualMidiPort() {
#ifdef _WIN32
	virtualMIDIShutdown(port);
	delete[] buffer;
#endif
}

void VirtualMidiPort::send(const std::vector<unsigned char>& data) {
#ifdef _WIN32
	virtualMIDISendData(port, const_cast<unsigned char*>(data.data()), data.size());
#else
	outPort.sendMessage(&data);
#endif
}

void VirtualMidiPort::join() {
	inListener.join();
}

void VirtualMidiPort::setCallback(const Callback& dataCallback) {
#ifdef _WIN32
	inListener = std::thread{ [this, dataCallback]() {
		unsigned long length;

		while (true) {
			virtualMIDIGetData(port, buffer, &length);
			std::vector<unsigned char> data(buffer, buffer + length);
			dataCallback(data);
		}
	} };
#else
	inListener = std::thread{ [this, dataCallback]() {
		std::vector<unsigned char> data;

		while (true) {
			inPort.getMessage(&data);
			if (data.size() != 0)
				dataCallback(data);

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	} };
#endif
}
