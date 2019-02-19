#include "DLLmain.h"

ExCellFile::ExCellFile(string szCellFile) : FileName(szCellFile)
{
	ptCellFile = D2WIN_LoadCellFile(szCellFile.c_str(), 0);
	if (!ptCellFile || (DWORD)ptCellFile == 1) // 26.01.2014 <-- fixed error when cell file fails to load
	{
		ptCellContext = 0;
		throw CellLoadError();
	}
	ptCellContext = new CellContext;
	memset(ptCellContext, 0, sizeof(CellContext));
	ptCellContext->pCellFile = ptCellFile;
}

ExCellFile::ExCellFile(CellFile* pCellFile)
{
	if (!pCellFile)
	{
		ptCellFile = 0;
		throw CellLoadError();
	}
	else
	{
		ptCellFile = pCellFile;
		ptCellContext = new CellContext;
		memset(ptCellContext, 0, sizeof(CellContext));
		ptCellContext->pCellFile = ptCellFile;
	}
}

CellContext* ExCellFile::Get()
{
	return ptCellContext ? ptCellContext : 0;
}

CellFile* ExCellFile::GetCF()
{
	return ptCellFile ? ptCellFile : 0;
}

bool ExCellFile::SetFrame(int No)
{
	if (!ptCellContext) return false;
	if (No > (int)ptCellContext->pCellFile->numcells) return false;
	ptCellContext->nFrame = No;
	return true;
}

ExCellFile::~ExCellFile(void)
{
	if (!ptCellFile) return;
	D2CMP_DeleteCellFile(ptCellFile);
	FOG_FreeClientMemory(ptCellFile, __FILE__, __LINE__, 0);
	ptCellFile = 0;
	if (!ptCellContext) return;
	delete ptCellContext;
	ptCellContext = 0;
}
