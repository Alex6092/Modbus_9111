#pragma once

#include <WS2tcpip.h>
#include <vector>

class ClientState
{
	SOCKET sock;
	std::vector<unsigned char> buffer;

public:
	ClientState(SOCKET sock);
	virtual ~ClientState();

	inline SOCKET getSocket() {
		return sock;
	}

	inline std::vector<unsigned char> & getBuffer() {
		return buffer;
	}
};

