#include <Windows.h>

static DWORD _ZIMU(DWORD d1, DWORD d2)
{
	return (d1 * d2);
}

static DWORD _ZOO3(DWORD d1, DWORD d2)
{
	return _ZIMU(d2, d1 >> 16);
}

static DWORD _ZOO1(DWORD d1, DWORD d2, DWORD d3)
{
	return _ZIMU(d2, d1) - _ZOO3(d1, d3);
}

static DWORD _ZOO2(DWORD d1, DWORD d2, DWORD d3)
{
	return _ZIMU(d2, d1) + _ZOO3(d1, d3);
}


namespace HashAlgorithms
{
	namespace PatentHash
	{
		bool __stdcall CS64_WordSwap(DWORD *pSrcStr, DWORD iChNum, DWORD *pdwMd5, DWORD *pOutInt)
		{
			DWORD dwRet0;
			DWORD dwRet1;
			DWORD dwMD5_0;
			DWORD dwMD5_1;

			if ( iChNum < 2 || iChNum & 1 )
				return false;
			dwMD5_0 = (pdwMd5[0] | 1) + 0x69FB0000;
			dwMD5_1 = (pdwMd5[1] | 1) + 0x13DB0000;
			dwRet1 = 0;
			dwRet0 = 0;
			for (DWORD i = 0; i < iChNum ; )
			{
				//////////////////////////////////////////////////////////////////////////
				DWORD dwTemp00 = dwRet0;
				if (i < iChNum)
				{
					dwTemp00 += pSrcStr[i];
				}
				DWORD dwTemp01 = _ZOO1(dwTemp00, dwMD5_0, 0x10FA9605);
				DWORD dwTemp02 = _ZOO2(dwTemp01, 0x79F8A395, 0x689B6B9F);
				DWORD dwTemp03 = _ZOO1(dwTemp02, 0xEA970001, 0x3C101569);
				i++;
				//////////////////////////////////////////////////////////////////////////
				DWORD dwTemp04 = dwTemp03;
				if (i < iChNum)
				{
					dwTemp04 += pSrcStr[i];
				}
				DWORD dwTemp05 = _ZOO1(dwTemp04, dwMD5_1, 0x3CE8EC25);
				DWORD dwTemp06 = _ZOO1(dwTemp05, 0x59C3AF2D, 0x2232E0F1);
				DWORD dwTemp07 = _ZOO2(dwTemp06, 0x1EC90001, 0x35BD1EC9);;
				i++;
				//////////////////////////////////////////////////////////////////////////
				dwRet0 = dwTemp07;
				dwRet1 = dwTemp03 + dwRet0 + dwRet1;
			}
			pOutInt[0] = dwRet0;
			pOutInt[1] = dwRet1;
			return true;
		}

		bool __stdcall CS64_Reversible(DWORD *pSrcStr, DWORD iChNum, DWORD *pdwMd5, DWORD *pOutInt)
		{
			DWORD dwRet0;
			DWORD dwRet1;
			DWORD dwMD5_0;
			DWORD dwMD5_1;

			if ( iChNum < 2 || iChNum & 1 )
				return false;
			dwRet1 = 0;
			dwRet0 = 0;
			dwMD5_0 = pdwMd5[0] | 1;
			dwMD5_1 = pdwMd5[1] | 1;

			for (DWORD i = 0; i < iChNum ; )
			{
				//////////////////////////////////////////////////////////////////////////
				DWORD dwTemp00 = dwRet0;
				if (i < iChNum)
				{
					dwTemp00 += pSrcStr[i];
				}
				DWORD dwTemp01 = dwMD5_0 * dwTemp00;
				DWORD dwTemp02 = _ZOO1(dwTemp01, 0xB1110000, 0x30674EEF);
				DWORD dwTemp03 = _ZOO1(dwTemp02, 0x5B9F0000, 0x78F7A461);
				DWORD dwTemp04 = _ZOO2(dwTemp03, 0xB96D0000, 0x12CEB96D);
				DWORD dwTemp05 = _ZOO2(dwTemp04, 0x1D830000, 0x257E1D83);
				i++;
				//////////////////////////////////////////////////////////////////////////
				DWORD dwTemp06 = dwTemp05;
				if (i < iChNum)
				{
					dwTemp06 += pSrcStr[i];
				}
				DWORD dwTemp07 = dwMD5_1 * dwTemp06;
				DWORD dwTemp08 = _ZOO1(dwTemp07, 0x16F50000, 0x5D8BE90B);
				DWORD dwTemp09 = _ZOO1(dwTemp08, 0x96FF0000, 0x2C7C6901);
				DWORD dwTemp10 = _ZOO2(dwTemp09, 0x2B890000, 0x7C932B89);
				DWORD dwTemp11 = _ZOO1(dwTemp10, 0x9F690000, 0x405B6097);
				i++;
				//////////////////////////////////////////////////////////////////////////
				dwRet0 = dwTemp11;
				dwRet1 = dwTemp05 + dwRet0 + dwRet1;
			}
			pOutInt[0] = dwRet0;
			pOutInt[1] = dwRet1;
			return true;
		}


		bool __stdcall BuildPatentHash_(DWORD *pWsStr, DWORD dwWsLen, DWORD *pMd5, QWORD *pOut)
		{
			DWORD dwCount;
			QWORD r1;
			QWORD r2;

			dwCount = dwWsLen / 4;
			if ( dwCount & 1 )
				--dwCount;
			if ( !HashAlgorithms::PatentHash::CS64_WordSwap(pWsStr, dwCount, pMd5, (DWORD *)&r1)
				||
				!HashAlgorithms::PatentHash::CS64_Reversible(pWsStr, dwCount, pMd5, (DWORD *)&r2) )
			{
				return false;
			}
			*pOut = r1 ^ r2;
			return true;
		}


	}
}
