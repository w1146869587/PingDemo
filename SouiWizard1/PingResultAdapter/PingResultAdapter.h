#pragma once
#include <helper/SAdapterBase.h>
struct CPingReresult
{
	std::string detiIp;
	DOUBLE bytes;
	DOUBLE time;
	DOUBLE ttl;
};

class CPingResultAdapter : public SOUI::SAdapterBase
{
public:
	CPingResultAdapter(std::vector<CPingReresult> &vecPingResult);
	~CPingResultAdapter();
	HRESULT UpdateResult(std::vector<CPingReresult> &vecPingResult);
protected:
	virtual int getCount();
	virtual void getView(int position, SOUI::SWindow * pItem, pugi::xml_node xmlTemplate);
	HRESULT _InitOneView(int postion, SOUI::SWindow *pItem);
private:
	std::vector<CPingReresult> m_vecPingResult;
};