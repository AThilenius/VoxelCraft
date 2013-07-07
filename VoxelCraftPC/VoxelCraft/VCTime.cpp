#include "VCTime.h"

INT64 VCTime::m_tickFrequancy = 0;
double VCTime::m_ticksPerSecond = 0;

VCTime::VCTime(void)
{
}


VCTime::~VCTime(void)
{
}

double VCTime::GetTime()
{
	if ( m_tickFrequancy == 0 )
	{
		QueryPerformanceFrequency((LARGE_INTEGER*) &m_tickFrequancy);
		m_ticksPerSecond = (double)(m_tickFrequancy);
	}

	INT64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER*) &currentTime);

	return ((double) currentTime / m_ticksPerSecond);
}
