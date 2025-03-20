#include "ClientState.h"



ClientState::ClientState(SOCKET sock)
{
	this->sock = sock;
}

ClientState::~ClientState()
{

}
