#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <Winhttp.h>

#include "extensions.h"
#include "puttymem.h"


/**
*
* Gets the IE proxy value
* Returns IE proxy from the system or NULL if there was any problem to get it
*
**/
ProxyData get_ie_proxy()
{
	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG MyProxyConfig;
	int set = FALSE;
	char *pch = NULL;
	const char *const WINDOW_TITLE = "Getting proxy"; 
	ProxyData result;

	result.port_num = -1;
	result.address = NULL;



	if(WinHttpGetIEProxyConfigForCurrentUser(&MyProxyConfig))
	{ 

		if(NULL != MyProxyConfig.lpszProxy) 
		{ 

			char* psz = (char *)malloc(sizeof(char) * (wcslen(MyProxyConfig.lpszProxy) + 1));
			wsprintfA(psz, "%S", MyProxyConfig.lpszProxy);
			GlobalFree(MyProxyConfig.lpszProxy);

			pch = strtok (psz, ":");

			while (pch != NULL)
			{
				if(set == FALSE)
				{
					result.address = _strdup(pch);
					set = TRUE;
				}
				else
				{
					if(pch!=NULL)
					{
						result.port_num = atoi(pch);
					}
				}

				pch = strtok (NULL, ":");
			}

			sfree(psz);
		}
		else
		{
			MessageBox(NULL, "Proxy is disabled", WINDOW_TITLE, MB_OK | MB_ICONEXCLAMATION);
		}
	}
	else 
	{
		MessageBox(NULL, "Can't get system proxy settings", WINDOW_TITLE, MB_OK | MB_ICONEXCLAMATION);
	}


	return result;


}