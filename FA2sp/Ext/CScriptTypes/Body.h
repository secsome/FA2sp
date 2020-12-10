#pragma once

#include <CScriptTypes.h>
#include "../FA2Expand.h"

#include <map>

// Forward Declartion
struct CScriptTypeAction;
struct CScriptTypeParam;

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

	void OnCBCurrentActionEditChanged();
	void OnCBScriptParameterEditChanged();

	/*void DoDataExchange(CDataExchange* pDX);

	void OnCBCurrentScriptSelectChanged();
	void OnLBScriptActionsSelectChanged();
	void OnETScriptNameChanged();
	
	void OnCBCurrentActionSelectChanged();
	void OnCBScriptParameterSelectChanged();
	void OnBNAddActionClicked();
	void OnBNDeleteActionClicked();
	void OnBNAddScriptClicked();
	void OnBNDeleteScriptClicked();*/

	CScriptTypesExt() {};
	~CScriptTypesExt() {};

	static std::map<int, CScriptTypeAction> ExtActions;
	static std::map<int, CScriptTypeParam> ExtParams;
};

struct CScriptTypeAction {
	const char* Name_;
	int ParamCode_;
	bool Hide_;
	bool Editable_;
	const char* Description_;
};

struct CScriptTypeParam {
	const char* Label_;
	int Param_;
};