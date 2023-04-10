#pragma once
#include <string>
#include <RtMidi.h>
#include "VirtualMidiPort.hpp"
#include "DeviceMidiPort.hpp"

class Sniffer {
public:
	Sniffer(std::string virtualPortName, unsigned int deviceInPort, unsigned int deviceOutPort);
	void join();

private:
	DeviceMidiPort devicePort;
	VirtualMidiPort virtualPort;

	void inCallback(const std::vector<unsigned char>& data);
	void outCallback(const std::vector<unsigned char>& message);
};