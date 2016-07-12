#include "time.h"

void Time::init(void){}

void Time::uninit(void){}

void Time::getTime(char *time){
	SYSTEMTIME SystemTime;
	CWA(kernel32,GetLocalTime)(&SystemTime);
	sprintf_s(time, MAX_TIME, "%d-%02d-%02d %02d:%02d:%02d",
		SystemTime.wYear,
		SystemTime.wMonth,
		SystemTime.wDay,
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond
		);
	return;
}

char * Time::getTime(){
	char *time = (char *)malloc(MAX_TIME);
	SYSTEMTIME SystemTime;
	CWA(kernel32, GetLocalTime)(&SystemTime);
	sprintf_s(time, MAX_TIME, "%d-%02d-%02d %02d:%02d:%02d",
		SystemTime.wYear,
		SystemTime.wMonth,
		SystemTime.wDay,
		SystemTime.wHour,
		SystemTime.wMinute,
		SystemTime.wSecond
		);
	return time;
}

int Time::_getLocalGmt(void)
{
	TIME_ZONE_INFORMATION tzi;
	int d = (int)CWA(kernel32, GetTimeZoneInformation)(&tzi);

	if (d == TIME_ZONE_ID_STANDARD)d = tzi.StandardBias;
	else if (d == TIME_ZONE_ID_DAYLIGHT)d = tzi.DaylightBias;
	else return 0;

	return (tzi.Bias + d) * (-60);
}

