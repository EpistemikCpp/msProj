#include "stdafx.h"
#include <mmsystem.h>
#include "resource.h"
#include "Sound.h"
/////////////////////////////////////////////////////////////////////////////
// Sound helpers

void PlaySound2(LPCTSTR lpszSound)
{
	HRSRC hRes; // resource handle to wave file
	HGLOBAL hData;
	BOOL bOk = FALSE;
	if ((hRes = ::FindResource(AfxGetResourceHandle(), lpszSound,
	  _T("sound"))) != NULL &&
	  (hData = ::LoadResource(AfxGetResourceHandle(), hRes)) != NULL)
	{
		// found the resource, play it
		bOk = sndPlaySound((LPCTSTR)::LockResource(hData),
			SND_MEMORY|SND_SYNC|SND_NODEFAULT);
		FreeResource(hData);
	}
	if (!bOk)
	{
		static BOOL bReported = FALSE;
		if (!bReported)
		{
			AfxMessageBox(IDS_CANNOT_PLAY_SOUND);
			bReported = TRUE;       // once please
		}
	}
}

void PlaySound1(UINT nIDS)
{
	PlaySound2(MAKEINTRESOURCE(nIDS));
}
