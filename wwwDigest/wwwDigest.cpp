#include "stdafx.h"
#include <stdio.h>
#include "digcalc.h"

int main(int argc, char ** argv) {
	char pszNonce[100];
	char * pszCNonce = "0a4f113b";
	char * pszUser = "Mufasa";
	char * pszRealm = "testrealm@host.com";
	char * pszPass = "Circle Of Life";
	char * pszAlg = "md5";
	char szNonceCount[9] = "00000001";
	char * pszMethod = "GET";
	char * pszQop = "auth";
	char * pszURI = "/dir/index.html";
	HASHHEX HA1;
	HASHHEX HA2 = "";
	HASHHEX Response;

	if (argc > 1)
		strcpy(pszNonce, argv[1]);
	else
		return -1;

	DigestCalcHA1(pszAlg, pszUser, pszRealm, pszPass, pszNonce, pszCNonce, HA1);
	DigestCalcResponse(HA1, pszNonce, szNonceCount, pszCNonce, pszQop,
		pszMethod, pszURI, HA2, Response);
	printf("Response = %s\n", Response);
	return 0;
};
