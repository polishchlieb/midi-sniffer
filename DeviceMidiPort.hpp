#pragma once
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <RtMidi.h>
#include "MidiPort.hpp"

class DeviceMidiPort : public MidiPort {
public:
	typedef std::function<void(const std::vector<unsigned char>& data)> Callback;

	DeviceMidiPort(unsigned int inPort, unsigned int outPort);

	void send(const std::vector<unsigned char>& data) override;
	void join() override;
	void setCallback(const Callback& dataCallback) override;
private:
	std::thread inListener;
	RtMidiIn inPort;
	RtMidiOut outPort;
};