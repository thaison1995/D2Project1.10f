#include "DLLmain.h"

void __fastcall NODES_AssignNode(Game *ptGame, UnitAny *ptUnit, DWORD pChild)
{
	int NEU_NODE = V_SetPlayers + 3;

	if (!ptGame) return;
	if (!ptUnit) return;
	if (ptUnit->dwType) return;
	if (ptUnit->dwNodeIndex != NEU_NODE) return;

	UnitNode** pNodes = ptGame->pNewNodes;

	for (int n = 0; n < V_SetPlayers; ++n)
	{
		if (!pNodes[n])
		{
			if ((INT)ptGame->nClients <= V_SetPlayers && n < V_SetPlayers)
			{
				UnitNode* ptUNode = (UnitNode*)FOG_AllocServerMemory(ptGame->pMemPools, sizeof(UnitNode), __FILE__, __LINE__, NULL);
				if (ptUNode)
				{
					ptUNode->pUnit = 0;
					ptUNode->dwArg = 0;
					ptUNode->pNext = 0;
					ptUNode->pPrev = 0;
					ptUNode->pUnit = ptUnit;
					ptUNode->dwArg = pChild;
					pNodes[n] = ptUNode;
					ptUnit->dwNodeIndex = n;
				}
			}
			break;
		}
	}
}

void __fastcall NODES_FreeUnitNode(Game* ptGame, UnitAny* ptUnit)
{
	int NEU_NODE = V_SetPlayers + 3;

	if (!ptGame) return;
	if (!ptUnit) return;
	if (ptUnit->dwType) return;
	if (ptUnit->dwType != UNIT_MONSTER) return;

	int aNodeIdx = ptUnit->dwNodeIndex;

	if (aNodeIdx == NEU_NODE) return;

	for (UnitNode* pNode = ptGame->pNewNodes[aNodeIdx]; pNode; pNode = pNode->pNext)
	{
		if (pNode->pUnit)
			pNode->pUnit->dwNodeIndex = NEU_NODE;
		FOG_FreeServerMemory(ptGame->pMemPools, pNode, __FILE__, __LINE__, 0);
	}

	ptGame->pNewNodes[aNodeIdx] = 0;
}

void __fastcall NODES_FreeChildNode(Game *ptGame, UnitAny *ptUnit)
{
	int NEU_NODE = V_SetPlayers + 3;

	if (!ptGame) return;
	if (!ptUnit) return;
	if (ptUnit->dwType > UNIT_MONSTER) return;

	int aNodeIdx = ptUnit->dwNodeIndex;
	if (aNodeIdx == NEU_NODE) return;

	UnitNode* pNode = ptGame->pNewNodes[aNodeIdx];
	if (!pNode) return;

	if (aNodeIdx >= V_SetPlayers)
	{
		while (pNode->pUnit != ptUnit)
		{
			pNode = pNode->pNext;
			if (!pNode)
			{
				ptUnit->dwNodeIndex = NEU_NODE;
				return;
			}
		}

		if (pNode == ptGame->pNewNodes[aNodeIdx])
		{
			ptGame->pNewNodes[aNodeIdx] = pNode->pNext;
			UnitNode* pChild = pNode->pNext;
			if (pChild) pChild->pPrev = 0;
			FOG_FreeServerMemory(ptGame->pMemPools, pNode, __FILE__, __LINE__, 0);
			ptUnit->dwNodeIndex = NEU_NODE;
			return;
		}
	}
	else
	{
		pNode = pNode->pNext;
		if (!pNode)
		{
			ptUnit->dwNodeIndex = NEU_NODE;
			return;
		}
		while (pNode->pUnit != ptUnit)
		{
			pNode = pNode->pNext;
			if (!pNode)
			{
				ptUnit->dwNodeIndex = NEU_NODE;
				return;
			}
		}
	}

	pNode->pPrev->pNext = pNode->pNext;
	UnitNode* pChild = pNode->pNext;
	if (pChild) pChild->pPrev = pNode->pPrev;
	FOG_FreeServerMemory(ptGame->pMemPools, pNode, __FILE__, __LINE__, 0);
	ptUnit->dwNodeIndex = NEU_NODE;
}

void __fastcall NODES_SetUnitNode(Game *ptGame, UnitAny *ptUnit, DWORD ptNode, int NodeIdx)
{
	int NEU_NODE = V_SetPlayers + 3;
	UnitNode *pParentNode;
	UnitNode *pCurrentNode;
	if (!ptGame || !ptUnit || ptUnit->dwNodeIndex != NEU_NODE || ptUnit->dwType > UNIT_MONSTER)
		return;

	if (NodeIdx != V_SetPlayers && NodeIdx != V_SetPlayers + 1)
		return;

	pCurrentNode = ptGame->pNewNodes[NodeIdx];

	pParentNode = (UnitNode*)FOG_AllocServerMemory(ptGame->pMemPools, sizeof(UnitNode), __FILE__, __LINE__, NULL);
	if (pParentNode)
	{
		pParentNode->pUnit = 0;
		pParentNode->dwArg = 0;
		pParentNode->pNext = 0;
		pParentNode->pPrev = 0;
		pParentNode->pUnit = ptUnit;
		pParentNode->dwArg = ptNode;
		ptGame->pNewNodes[NodeIdx] = pParentNode;
		if (pCurrentNode)
		{
			pParentNode->pNext = pCurrentNode;
			pCurrentNode->pPrev = pParentNode;
		}
		ptUnit->dwNodeIndex = NodeIdx;
	}
	else
	{
		Log("NodesEx: No memory to allocate a node");
	}
}

void __fastcall NODES_AddAsParentNode(Game *ptGame, UnitAny *ptUnit, DWORD ptNode, int NodeIdx)
{
	int NEU_NODE = V_SetPlayers + 3;
	if (!ptGame || !ptUnit) return;
	if (ptUnit->dwNodeIndex != NEU_NODE) return;
	if (NodeIdx >= V_SetPlayers) return;
	if (ptUnit->dwType > UNIT_MONSTER) return;

	UnitNode * pCurrentNode = ptGame->pNewNodes[NodeIdx];
	if (pCurrentNode)
	{
		if (pCurrentNode->pUnit)
		{
			UnitNode * pParentNode = (UnitNode*)FOG_AllocServerMemory(ptGame->pMemPools, sizeof(UnitNode), __FILE__, __LINE__, NULL);
			if (pParentNode)
			{
				pParentNode->pUnit = 0;
				pParentNode->dwArg = 0;
				pParentNode->pNext = 0;
				pParentNode->pPrev = 0;
				pParentNode->pUnit = ptUnit;
				pParentNode->dwArg = ptNode;
				pParentNode->pNext = pCurrentNode->pNext;
				pParentNode->pPrev = pCurrentNode;
				UnitNode * pChildNode = pCurrentNode->pNext;
				if (pChildNode)
					pChildNode->pPrev = pParentNode;
				pCurrentNode->pNext = pParentNode;
				ptUnit->dwNodeIndex = NodeIdx;
			}
		}
	}
}

void UnitNodes::OnPatch()
{
	int NEU_NODE = V_SetPlayers + 3;

	Patch(JUMP, "D2Game.dll", 0x10170, (DWORD)NODES_AssignNode, 6, "NodesEX: Alloc 16-players nodes");
	Patch(JUMP, "D2Game.dll", 0x10310, (DWORD)NODES_FreeUnitNode, 6, "NodesEX: Free 16-players nodes");
	Patch(JUMP, "D2Game.dll", 0x10380, (DWORD)NODES_FreeChildNode, 8, "NodesEX: Free Child of 16-players nodes");
	Patch(JUMP, "D2Game.dll", 0x10280, (DWORD)NODES_SetUnitNode, 6, "NodesEX: Set Unit Node As Parent (Monsters)");
	Patch(JUMP, "D2Game.dll", 0x101F0, (DWORD)NODES_AddAsParentNode, 6, "NodesEX: Set Unit Node As Parent (Players)");

	Patch(0, "D2Game.dll", 0xB881A + 2, V_SetPlayers, 1, "NULL");
	Patch(0, "D2Game.dll", 0xC2480 + 2, V_SetPlayers, 1, "NULL");
	Patch(0, "D2Game.dll", 0x9D778 + 2, V_SetPlayers, 1, "NULL");

	Patch(0, "D2Game.dll", 0xC21A4, 0x1E00, 4, "NodesEX: Change node offset I");
	Patch(0, "D2Game.dll", 0xC21AA, 0x1E00, 4, "NodesEX: Change node offset II");
	Patch(0, "D2Game.dll", 0xB86FF, 0x1E00, 4, "NodesEX: Change node offset III");
	Patch(0, "D2Game.dll", 0xB8705, 0x1E00, 4, "NodesEX: Change node offset IV");
	Patch(0, "D2Game.dll", 0x9D666, 0x1E00, 4, "NodesEX: Change node offset V");
	Patch(0, "D2Game.dll", 0x9D66C, 0x1E00, 4, "NodesEX: Change node offset VI");

	//Basic fixes
	Patch(0, "D2Game.dll", 0x1879, V_SetPlayers, 1, "GameEnter: Check number of players");
	Patch(0, "D2Game.dll", 0x2606, V_SetPlayers, 1, "GameEnter: Check number of players II");

	//Patch(CUSTOM, "D2GS.exe", 0x240C, V_SetPlayers, 1, "GameEnter: Check number of players III");
	//Patch(CUSTOM, "D2GS.exe", 0x4FD4, V_SetPlayers, 1, "GameEnter: Check number of players IV");

	//TREASURE Class
	Patch(0, "D2Game.dll", 0x21519, V_SetPlayers, 1, "NodesEX: Fix Treasure Class Drop");
	Patch(0, "D2Game.dll", 0x2151F, V_SetPlayers, 1, "NodesEX: Fix Treasure Class Drop II");

	Patch(0, "D2Game.dll", 0x8B87D, NEU_NODE, 4, "NodesEX: Create UnitAny: Change neutral Node");

	Patch(0, "D2Game.dll", 0x9483A, V_SetPlayers, 1, "NodesEX: Change Players Nodes from 8");
	Patch(0, "D2Game.dll", 0x9485D, NEU_NODE, 1, "NodesEX: Change neutral Node");

	Patch(0, "D2Game.dll", 0x94434, V_SetPlayers, 1, "NodesEX: RemoveMonsterCorpse: Change iteration to 16");

	//Missiles
	Patch(0, "D2Game.dll", 0xBEDD6, V_SetPlayers, 1, "NodesEX: MONAI_WUSSIE: Change iteration to 16");
	Patch(0, "D2Game.dll", 0x37B66, V_SetPlayers, 1, "NodesEX: Rogue Scout spawn: Change iteration to 16");

	Patch(0, "D2Game.dll", 0xBE48D + 1, V_SetPlayers, 1, "NULL");
	Patch(0, "D2Game.dll", 0x2810B + 1, NEU_NODE - 2, 1, "NULL");
	Patch(0, "D2Game.dll", 0x93C01 + 1, NEU_NODE - 2, 1, "NULL");
	Patch(0, "D2Game.dll", 0xDBC79 + 1, NEU_NODE - 2, 1, "NULL");
	Patch(0, "D2Game.dll", 0xDC247 + 1, NEU_NODE - 2, 1, "NULL");
	Patch(0, "D2Game.dll", 0xDE29D + 1, NEU_NODE - 2, 1, "NULL");
	Patch(0, "D2Game.dll", 0xDE68B + 1, NEU_NODE - 2, 1, "NULL");
	Patch(0, "D2Game.dll", 0xBE47B, NEU_NODE, 1, "NULL");
}