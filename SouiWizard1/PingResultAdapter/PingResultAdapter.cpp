#include "stdafx.h"
#include <helper/SAdapterBase.h>
#include "PingResultAdapter.h"

CPingResultAdapter::CPingResultAdapter(std::vector<CPingReresult> &vecPingResult) : m_vecPingResult(vecPingResult)
{
	
}

CPingResultAdapter::~CPingResultAdapter()
{

}

HRESULT CPingResultAdapter::UpdateResult(std::vector<CPingReresult> &vecPingResult)
{
	m_vecPingResult = vecPingResult;
	return S_OK;
}

int CPingResultAdapter::getCount()
{
	return m_vecPingResult.size();
}

void CPingResultAdapter::getView(int position, SWindow * pItem, pugi::xml_node xmlTemplate)
{
	if (pItem->GetChildrenCount() == 0) {
		pItem->InitFromXml(xmlTemplate);
	}

	_InitOneView(position, pItem);
}

HRESULT CPingResultAdapter::_InitOneView(int postion, SWindow *pItem)
{
	SOUI::SStringW strStr;
	SOUI::SWindow *pFrom = pItem->FindChildByName2<SOUI::SWindow>(L"text_from");
	assert(pFrom);
	LPCSTR str= (LPCSTR)m_vecPingResult[postion].detiIp.c_str();
	int   nLen = strlen(str) + 1;
	int   nwLen = MultiByteToWideChar(CP_ACP, 0, str, nLen, NULL, 0);
	TCHAR   tStr[256];
	MultiByteToWideChar(CP_ACP, 0, str, nLen, tStr, nwLen);
	pFrom->SetWindowText(tStr);

	SOUI::SWindow *pBytes = pItem->FindChildByName2<SOUI::SWindow>(L"text_bytes");
	assert(pBytes);
	strStr.Format(L"%.2f", m_vecPingResult[postion].bytes);
	pBytes->SetWindowText(strStr);

	SOUI::SWindow *pTime = pItem->FindChildByName2<SOUI::SWindow>(L"text_time");
	assert(pTime);
	strStr.Format(L"%.2f", m_vecPingResult[postion].time);
	pTime->SetWindowText(strStr);

	SOUI::SWindow *pTTL = pItem->FindChildByName2<SOUI::SWindow>(L"text_ttl");
	assert(pTTL);
	strStr.Format(L"%.2f", m_vecPingResult[postion].ttl);
	pTTL->SetWindowText(strStr);

	return S_OK;
}
