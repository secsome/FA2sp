#include "Body.h"

#include "../../Helpers/Translations.h"

#include <CINI.h>

void CLightingExt::ProgramStartupInit()
{
	RunTime::ResetMemoryContentAt(0x594788, &CLightingExt::PreTranslateMessageExt);
}

void CLightingExt::Translate()
{
	Translations::TranslateItem(this, "LightingTitle");
	Translations::TranslateItem(this, 1285, "LightingDesc");
	Translations::TranslateItem(this, 1298, "LightingNormal");
	Translations::TranslateItem(this, 1299, "LightingIonStorm");
	Translations::TranslateItem(this, 1320, "LightingDominator");

	// Normal
	Translations::TranslateItem(this, 1300, "LightingAmbient");
	Translations::TranslateItem(this, 1305, "LightingGreen");
	Translations::TranslateItem(this, 1304, "LightingRed");
	Translations::TranslateItem(this, 1306, "LightingBlue");
	Translations::TranslateItem(this, 1301, "LightingLevel");
	Translations::TranslateItem(this, 1315, "LightingGround");

	// IonStorm
	Translations::TranslateItem(this, 1302, "LightingAmbient");
	Translations::TranslateItem(this, 1308, "LightingGreen");
	Translations::TranslateItem(this, 1307, "LightingRed");
	Translations::TranslateItem(this, 1309, "LightingBlue");
	Translations::TranslateItem(this, 1303, "LightingLevel");
	Translations::TranslateItem(this, 1316, "LightingGround");

	// Dominator
	Translations::TranslateItem(this, 1310, "LightingAmbient");
	Translations::TranslateItem(this, 1311, "LightingGreen");
	Translations::TranslateItem(this, 1312, "LightingRed");
	Translations::TranslateItem(this, 1313, "LightingBlue");
	Translations::TranslateItem(this, 1314, "LightingLevel");
	Translations::TranslateItem(this, 1317, "LightingGround");

	// Others
	Translations::TranslateItem(this, 1318, "LightingNukeAmbientChangeRate");
	Translations::TranslateItem(this, 1319, "LightingDominatorAmbientChangeRate");
}

BOOL CLightingExt::PreTranslateMessageExt(MSG* pMsg)
{
	if (pMsg->message == EN_KILLFOCUS || pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		auto process = [&pMsg, this](int nID, const char* pKey) -> bool
		{
			auto pWnd = (ppmfc::CWnd*)this->GetDlgItem(nID);
			if (pMsg->hwnd == pWnd->m_hWnd)
			{
				ppmfc::CString buffer;
				pWnd->GetWindowText(buffer);

				double temp;
				if (sscanf_s(buffer, "%lf", &temp) == 1)
					buffer.Format("%.6f", temp);
				else
				{
					buffer = "0.000000";
					pWnd->SetWindowText(buffer);
				}
				CINI::CurrentDocument->WriteString("Lighting", pKey, buffer);

				return true;
			}
			return false;
		};

		if (!process(1068, "DominatorAmbient"))
		if (!process(1069, "DominatorGreen"))
		if (!process(1070, "DominatorRed"))
		if (!process(1071, "DominatorBlue"))
		if (!process(1072, "DominatorLevel"))
		if (!process(1073, "Ground"))
		if (!process(1074, "IonGround"))
		if (!process(1075, "DominatorGround"))
		if (!process(1076, "NukeAmbientChangeRate"))
		if (!process(1077, "DominatorAmbientChangeRate"))
		;

	}
	return this->FA2CDialog::PreTranslateMessage(pMsg);
}