#pragma once

#include <CScriptTypes.h>
#include "../FA2Expand.h"

#include <map>

// Forward Declartion
struct CScriptTypeUnit;

class NOVTABLE CScriptTypesExt : public CScriptTypes
{
public:
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();

	//
	// Ext Functions
	//

	BOOL OnInitDialog();
	void DoDataExchange(CDataExchange* pDX);
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
	void OnBNDeleteScriptClicked();


	CScriptTypesExt() {};
	~CScriptTypesExt() {};

private:

};

struct CScriptTypeUnit
{
	CScriptTypeUnit() = default;
	CScriptTypeUnit(const char* lpSrc);

	int Index;
	char Name[0x80];
	int ParamType;
	char Description[0x400];
	bool DisplayInList;
};

// Statics
static std::map<int, CScriptTypeUnit> ExtMap;