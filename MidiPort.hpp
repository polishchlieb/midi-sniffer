#pragma once
#include <mutex>
#include <functional>
#include <vector>

class MidiPort {
public:
	typedef std::function<void(const std::vector<unsigned char>& data)> Callback;

	virtual void send(const std::vector<unsigned char>& data) = 0;
	virtual void join() = 0;
	virtual void setCallback(const Callback& dataCallback) = 0;
};