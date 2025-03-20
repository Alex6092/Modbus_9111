#pragma once

#include "ClientState.h"
#include <vector>
#include <set>
#include <map>

template<class CS>
class Parser
{
private:
	std::map<SOCKET, CS *> socketToClientMap;

protected:
	inline std::map<SOCKET, CS *> & getConnectedClients() {
		return socketToClientMap;
	}

public:
	virtual ~Parser();

	virtual void onClientConnected(CS * client);
	void parse(SOCKET sock, unsigned char * buf, int length);
	virtual void parse(CS * client, std::vector<unsigned char> & receivedPacket) = 0;
	void onClientDisconnected(SOCKET sock);
	virtual void onClientDisconnected(CS * client);
};

template<class CS>
Parser<CS>::~Parser()
{
}

template<class CS>
void Parser<CS>::onClientConnected(CS * client) {
	socketToClientMap[client->getSocket()] = client;
}


template<class CS>
void Parser<CS>::parse(SOCKET sock, unsigned char * buf, int length)
{
	auto it = socketToClientMap.find(sock);
	if (it != socketToClientMap.end())
	{
		std::vector<unsigned char> receivedData;
		for (int i = 0; i < length; i++)
			receivedData.push_back(buf[i]);
		parse(socketToClientMap[sock], receivedData);
	}
}

template<class CS>
void Parser<CS>::onClientDisconnected(SOCKET sock) {
	auto it = socketToClientMap.find(sock);
	if (it != socketToClientMap.end())
	{
		onClientDisconnected(socketToClientMap[sock]);
	}
}

template<class CS>
void Parser<CS>::onClientDisconnected(CS * client) {
	socketToClientMap.erase(client->getSocket());
	delete client;
}