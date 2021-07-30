#include "Body.h"

#include <GlobalVars.h>

#include "../../Helpers/STDHelpers.h"
#include "../../Helpers/Translations.h"

void CTriggerEventExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x597D44, &CTriggerEventExt::OnInitDialogExt);
	RunTime::ResetMemoryContentAt(0x597D18, &CTriggerEventExt::PreTranslateMessageExt);
}

BOOL CTriggerEventExt::OnInitDialogExt()
{
	BOOL ret = this->CTriggerEvent::OnInitDialog();
	if (!ret)
		return FALSE;

	Translations::TranslateItem(this, 50500, "TriggerEventCurrent");
	Translations::TranslateItem(this, 50501, "TriggerEventOptions");
	Translations::TranslateItem(this, 50502, "TriggerEventType");
	Translations::TranslateItem(this, 50503, "TriggerEventParameter");
	Translations::TranslateItem(this, 50504, "TriggerEventParamValue");
	Translations::TranslateItem(this, 50505, "TriggerEventDesc");

	Translations::TranslateItem(this, 1396, "TriggerEventNew");
	Translations::TranslateItem(this, 1169, "TriggerEventDel");
	Translations::TranslateItem(this, 50506, "TriggerEventCopy");

	return TRUE;
}

BOOL CTriggerEventExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP)
	{
		if (pMsg->hwnd == this->GetDlgItem(50506)->GetSafeHwnd())
			this->OnBNCloneEventClicked();

	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}

void CTriggerEventExt::OnBNCloneEventClicked()
{
	if (!this->EventID.IsEmpty() && this->CCBCurrentEvent.GetCount() > 0)
	{
		int nEventIndex = this->CCBCurrentEvent.GetCurSel();
		if (nEventIndex != CB_ERR)
		{
			ppmfc::CString data = GlobalVars::INIFiles::CurrentDocument->GetString("Events", this->EventID);
			auto splitResults = STDHelpers::SplitString(data);
			int count = atoi(splitResults[0].c_str());
			int beginIndex = 1;
			for (int i = 0; i < nEventIndex; ++i)
				beginIndex += atoi(splitResults[beginIndex + 1].c_str()) == 2 ? 4 : 3;
			int eventSize = atoi(splitResults[beginIndex + 1].c_str()) == 2 ? 4 : 3;
			
			data.Format("%d,", count + 1);
			for (int i = 1; i < splitResults.size(); ++i)
			{
				data += splitResults[i].c_str();
				data += ",";
			}
			for (int i = 0; i < eventSize - 1; ++i)
			{
				data += splitResults[beginIndex + i].c_str();
				data += ",";
			}
			data += splitResults[beginIndex + eventSize - 1].c_str();
			GlobalVars::INIFiles::CurrentDocument->WriteString("Events", this->EventID, data);

			ppmfc::CString buffer;

			if (!Translations::GetTranslationItem("Event", data))
				data = "Event";

			buffer.Format("%s %d", data, count);
			int nNewIdx = this->CCBCurrentEvent.AddString(buffer);
			this->CCBCurrentEvent.SetItemData(nNewIdx, count);
			this->CCBCurrentEvent.SetCurSel(nNewIdx);

			this->OnCBCurrentEventSelChanged();
		}
	}
}