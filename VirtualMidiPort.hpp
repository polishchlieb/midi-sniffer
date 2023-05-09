#pragma once
#include <string>
#include <thread>
#include "MidiPort.hpp"

#ifdef _WIN32
#include <teVirtualMIDI.h>
#else
#include <RtMidi.h>
#endif

class VirtualMidiPort : public MidiPort {
public:
	typedef std::function<void(const std::vector<unsigned char>& data)> Callback;

	VirtualMidiPort(std::string name);
	~VirtualMidiPort();

	void send(const std::vector<unsigned char>& data) override;
	void join() override;
	void setCallback(const Callback& dataCallback) override;
private:
	std::thread inListener;
#ifdef _WIN32
	LPVM_MIDI_PORT port;
	unsigned char* buffer;
#else
	RtMidiIn inPort;
	RtMidiOut outPort;
#endif
};