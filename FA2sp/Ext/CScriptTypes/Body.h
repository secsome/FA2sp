#pragma once

#include <CScriptTypes.h>
#include "../FA2Expand.h"

#include <map>

// Forward Declartion
struct CScriptTypeAction;

class NOVTABLE CScriptTypesExt : public CScriptTypes
{
public:
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	//
	// Ext Functions
	//

	/*static void* GetMessageMap();*/

	BOOL OnInitDialog();
	/*void DoDataExchange(CDataExchange* pDX);

	void OnCBCurrentScriptSelectChanged();
	void OnLBScriptActionsSelectChanged();
	void OnETScriptNameChanged();
	void OnCBCurrentActionEditChanged();
	void OnCBCurrentActionSelectChanged();
	void OnCBScriptParameterEditChanged();
	void OnCBScriptParameterSelectChanged();
	void OnBNAddActionClicked();
	void OnBNDeleteActionClicked();
	void OnBNAddScriptClicked();
	void OnBNDeleteScriptClicked();*/

	CScriptTypesExt() {};
	~CScriptTypesExt() {};

	static std::map<int, CScriptTypeAction> ExtActions;
};

struct CScriptTypeAction {
	const char* Name_;
	int ParamCode_;
	bool Hide_;
	bool Editable_;
	const char* Description_;
};