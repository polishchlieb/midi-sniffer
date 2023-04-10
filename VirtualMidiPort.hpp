#pragma once
#include <string>
#include <vector>
#include <functional>
#include <thread>

#ifdef _WIN32
#include <teVirtualMIDI.h>
#else
#include <RtMidi.h>
#endif

class VirtualMidiPort {
public:
	typedef std::function<void(const std::vector<unsigned char>& data)> Callback;

	VirtualMidiPort(std::string name);
	~VirtualMidiPort();

	void send(const std::vector<unsigned char>& data);
	void join();
	void setCallback(const Callback& dataCallback);
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