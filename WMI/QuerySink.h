#pragma once

#ifndef QUERYSINK_H
#define QUERYSIN_H

#define _WIN32_DCOM
#include<comdef.h>
#include<WbemIdl.h>

#pragma comment(lib,"wbemuuid.lib")

class QuerySink : public IWbemObjectSink
{
	LONG m_lRef;
	bool bDone;

	CRITICAL_SECTION threadLock;

public:
	QuerySink() { m_lRef = 0, bDone = false; InitializeCriticalSection(&threadLock); };
};

#endif // !QUERYSINK_H
