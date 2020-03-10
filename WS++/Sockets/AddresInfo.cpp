#include "AddresInfo.h"

void AddressInfo::free(Ptr ptr)
{
	freeaddrinfo(ptr);
}

AddressInfo::AutoDelete AddressInfo::get(PCSTR pNodeName, PCSTR pServiceName, const ADDRINFOA* pHints)
{
	// Ensuring WSAStartup had been called
	_WSA::get_main();

	addrinfo* info;
	int status = getaddrinfo(pNodeName, pServiceName, pHints, &info);
	if (status != 0)
	{
		throw Socket::Error("Could not get address info", WSAGetLastError());
	}
	return AutoDelete(info);
}

void AddressInfo::Deleter::operator()(Ptr t)
{
	AddressInfo::free(t);
}
