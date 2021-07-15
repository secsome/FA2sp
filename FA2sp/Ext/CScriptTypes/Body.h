#pragma once

#include <CScriptTypes.h>
#include "../FA2Expand.h"

#include <map>

// Forward Declartion
struct CScriptTypeAction;
struct CScriptTypeParam;
class CurrentScript;

class NOVTABLE CScriptTypesExt : public CScriptTypes
{
public:
	BOOL PreTranslateMessageExt(MSG* pMsg);

	static void ProgramStartupInit();


	void UpdateParams(int actionIndex);

	//
	// Ext Functions
	//

	/*static void* GetMessageMap();*/

	BOOL OnInitDialogExt();

	void OnCBCurrentActionEditChanged();
	void OnCBScriptParameterEditChanged();
	void OnLBScriptActionsSelectChanged();

	/*void DoDataExchange(CDataExchange* pDX);

	void OnCBCurrentScriptSelectChanged();
	void OnETScriptNameChanged();
	
	void OnCBCurrentActionSelectChanged();
	void OnCBScriptParameterSelectChanged();
	*/
	void OnBNAddActionClickedExt();
	/*
	void OnBNDeleteActionClicked();
	void OnBNAddScriptClicked();
	void OnBNDeleteScriptClicked();*/
	
	//void OnBNDeleteActionClicked();
	void OnBNAddScriptClickedExt();
	//void OnBNDeleteScriptClicked();


	CScriptTypesExt() {};
	~CScriptTypesExt() {};

	// Functional Functions
	void OnBNCloneScriptClicked();
	void OnBNCloneItemClicked();

	static CurrentScript ExtCurrentScript;
};

struct CScriptTypeAction {
	static std::map<int, CScriptTypeAction> ExtActions;

	ppmfc::CString Name_;
	int ParamCode_;
	bool Hide_;
	bool Editable_;
	ppmfc::CString Description_;
};

struct CScriptTypeParam {
	static std::map<int, CScriptTypeParam> ExtParams;

	ppmfc::CString Label_;
	int Param_;
};

class CurrentScript {
public:
	struct ScriptNode {
		ScriptNode() : Type{ -1 }, Param{ -1 }{}
		bool IsEmpty() { return Type == -1 && Param == -1; }
		void MakeEmpty() { Type = -1; Param = -1; }

		int Type;
		union {
			int Param;
			struct {
				short ParamExt;
				short ParamNormal;
			};
		};
	};

	ppmfc::CString ID;
	ppmfc::CString Name;
	ScriptNode Actions[50];
	int Count;

	ppmfc::CString ToString();
	ppmfc::CString GetActionString(int index);
	int AddAction(ScriptNode& node);
	int AddAction(int type, int param);
	int AddAction(int type, short param, short ext);
	bool AddActionAt(ScriptNode& node, int index);
	bool AddActionAt(int type, int param, int index);
	bool AddActionAt(int type, short param, short ext, int index);
	int GetActionCount();
	ScriptNode& RemoveActionAt(int index);
	void Set(ppmfc::CString id);
	void Write(ppmfc::CString id, ppmfc::CString name);
	void Write();
};