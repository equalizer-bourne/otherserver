#include "MiniAprPch.h"
#include "ProfilerStrategy_Average.h"

using namespace MINIAPR;

#define PROFILEMODULE	"Profile"

extern "C"  IComponent* createProfileStrategyAverage(Int32 /*dwVersion*/)
{
	return new ProfilerStrategyAverage;
}

ProfilerStrategyAverage::ProfilerStrategyAverage():m_pTimerManager(NULL)
{}

ProfilerStrategyAverage::~ProfilerStrategyAverage()
{}

bool ProfilerStrategyAverage::initlize(const PropertySet& propSet)
{
	m_nTimeInterval = propSet.getInt(2, 120000);

	if(!m_pTimerManager)
	{
		MINIAPR_ERROR("δ�����������TimeAxis\n");
		return false;
	}
	

	m_pTimerManager->setTimer(this, 1, m_nTimeInterval, "Profile");

	return true;
}

bool ProfilerStrategyAverage::inject(const std::string& componentName, IComponent* pComponent)
{
	if(pComponent->queryInterface(IID_ITimerComponent) )
	{
		m_pTimerManager = static_cast<ITimerComponent*>(pComponent->queryInterface(IID_ITimerComponent) );
	}

	return true;
}

void ProfilerStrategyAverage::onTimer(int /*nEventId*/)
{
	// Ok ��ʱ��д������־��
	FDLOG(PROFILEMODULE)<<"��ʼд������־****************************************************"<<endl;
	char szTmpMsg[4096] = {0};
	snprintf(szTmpMsg, sizeof(szTmpMsg), "%-32s%-10s%-10s%-10s%-15s%-15s", "������","ִ�д���", "��Сʱ��", "ƽ��ʱ��", "���ʱ��", "ʱ��ռ����");
	FDLOG(PROFILEMODULE)<<szTmpMsg<<endl;
	for(MapProfileData::iterator it = m_profileDataMap.begin(); it != m_profileDataMap.end(); it++)
	{
		if(0 == it->second.nCount) continue;

		snprintf(szTmpMsg, sizeof(szTmpMsg), "%-32s%-10d%-10d%-10d%-15d %6f%%", it->first.c_str(), it->second.nCount, it->second.dwMinMicroseconds, it->second.dwTotalMicroseconds/it->second.nCount, 
			it->second.dwMaxMicroseconds, (double)it->second.dwTotalMicroseconds/((double)m_nTimeInterval * 10));

		FDLOG(PROFILEMODULE)<<szTmpMsg<<endl;
		it->second.dwMaxMicroseconds = 0;
		it->second.dwMinMicroseconds = 0;
		it->second.dwTotalMicroseconds = 0;
		it->second.nCount = 0;
	}
	FDLOG(PROFILEMODULE)<<"����������־******************************************************"<<endl;

	// ��¼����������־
	FDLOG(PROFILEMODULE)<<"��ʼ�����������******************************************************"<<endl;
	snprintf(szTmpMsg, sizeof(szTmpMsg), "%-48s%-15s%-15s", "������", "��������", "���������С");
	for(std::map<string, int>::iterator it = m_mapObjCount.begin(); it != m_mapObjCount.end(); it++)
	{
		snprintf(szTmpMsg, sizeof(szTmpMsg), "%-48s%-15d%-15d", it->first.c_str(), it->second, m_mapObjSize[it->first]);
		FDLOG(PROFILEMODULE)<<szTmpMsg<<endl;
	}

	FDLOG(PROFILEMODULE)<<"���������������******************************************************"<<endl;
}

void ProfilerStrategyAverage::onBeginProfiler(const std::string& strProfilerName, Uint64 ddTimer)
{
	MapProfileData::iterator it = m_profileDataMap.find(strProfilerName);
	if(it == m_profileDataMap.end() )
	{
		ProfileAverageData data;
		data.nCount = 0;
		data.dwTotalMicroseconds = 0;
		data.dwMaxMicroseconds = 0;
		data.dwMinMicroseconds = 0;
		data.ddBeginTime = 0;
		it = m_profileDataMap.insert(std::make_pair(strProfilerName, data) ).first;
	}
	
	it->second.ddBeginTime = ddTimer;
}

void ProfilerStrategyAverage::onEndProfiler(const std::string& strProfilerName, Uint64 ddTimer)
{
	MapProfileData::iterator it = m_profileDataMap.find(strProfilerName);
	if(it == m_profileDataMap.end() ) void();//APR_ERROR("���ֲ����ڵ�Profile:%s", strProfilerName.c_str() );
	
	Uint32 dwUseTime = (Uint32)(ddTimer - it->second.ddBeginTime);
	it->second.nCount++;
	it->second.dwTotalMicroseconds += dwUseTime;
	if( (it->second.dwMinMicroseconds > dwUseTime) || (0 == it->second.dwMinMicroseconds) )  it->second.dwMinMicroseconds = dwUseTime;
	if(it->second.dwMaxMicroseconds < dwUseTime) it->second.dwMaxMicroseconds = dwUseTime;
}


void ProfilerStrategyAverage::onObjCountInc(const std::string& strClassName, int iSingleSize)
{
	std::map<string, int>::iterator it = m_mapObjCount.find(strClassName);
	if(it == m_mapObjCount.end() )
	{
		m_mapObjSize[strClassName] = iSingleSize;
		m_mapObjCount[strClassName] = 1;
	}
	else
	{
		it->second++;
	}
}

void ProfilerStrategyAverage::onObjCountDec(const std::string& strClassName)
{
	std::map<string, int>::iterator it = m_mapObjCount.find(strClassName);
	assert(it != m_mapObjCount.end() );
	it->second--;
}


