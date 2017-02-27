
//the function will reset some global variable for others function check
#include "CMD5Checksum.h"
#include "BaseScene.h"

#define VALID_FILE_NAME		"key"

extern int DES_DecryptFromFile(const char *cipherFile, const char *keyStr,  char *plainStr);
extern int DES_EncryptToFile(const char *plainStr, char *keyStr,const char *cipherFile);
extern int getMacInternal( char mac[40] );

bool validCheck( )
{
	char plain[1024] ;
    memset( plain , 0 , 1024 );
    

	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + VALID_FILE_NAME;

	char mac[40] ;
	memset( mac , 0 , 40 );

	int ret = getMacInternal( mac );

	int length = DES_DecryptFromFile( path.c_str(), mac , plain );
		
	//encrypt and write to file 
	
	if( length > 0 )
	{
		int md5Length = (int)(plain[0]);
		std::string md5_calculate = CMD5Checksum::GetMD5OfChar( plain + md5Length + 1  );

		if( md5_calculate.size() ==  md5Length )
		{ // size ==
			if( memcmp( md5_calculate.c_str() ,plain + 1, md5Length  ) == 0 )
			{// =
				BaseScene::validCheckPass = true;
				return true;
			}
			else
			{//!=
				BaseScene::validCheckPass = false;
				return false;
			}
		}
		else
		{ //size !=
			BaseScene::validCheckPass = false;
			return false;
		}
	}
	else
	{
		BaseScene::validCheckPass = false;
		return false;
	}
	return false;

}

// 1 byte
//md5length md5 mac
void generateValidFile()
{
	//get mac address
	char mac[40] ;
	memset( mac , 0 , 40 );

	int ret = getMacInternal( mac );

	//calculate md5
	
	if( ret > 0 )
	{
		std::string md5 = CMD5Checksum::GetMD5OfChar( mac  );

	
		// join encrytp data and md5 

		char md5length[2] ;
		md5length[0] =  (char)(md5.size());
		md5length[1] = 0;

		std::string joinStr =md5length ;

		joinStr.append(md5);
		joinStr.append( mac );

		char key[8] ;
		memcpy( key  , mac , 8 );

		std::string path = CCFileUtils::sharedFileUtils()->getWritablePath() + VALID_FILE_NAME;

		//encrypt and write to file 
		DES_EncryptToFile( joinStr.c_str() , mac , path.c_str() );
		
	}


}

#ifdef _WINDOWS
#include <winsock2.h>
#include <Iphlpapi.h>
#include <stdio.h>
#pragma comment(lib,"Iphlpapi.lib")

void byte2Hex(unsigned char bData,unsigned char hex[])
{
    int high=bData/16,low =bData %16;
    hex[0] = (high <10)?('0'+high):('A'+high-10);
    hex[1] = (low <10)?('0'+low):('A'+low-10);
}

int getMacInternal( char mac[40] )
{
	unsigned long ulSize=0;
    PIP_ADAPTER_INFO pInfo=NULL;
    int temp=0;
    temp = GetAdaptersInfo(pInfo,&ulSize);//第一处调用，获取缓冲区大小
    pInfo=(PIP_ADAPTER_INFO)malloc(ulSize);
    temp = GetAdaptersInfo(pInfo,&ulSize);
 
    int iCount=0;
    while(pInfo)//遍历每一张网卡
    {
        //  pInfo->Address MAC址
        for(int i=0;i<(int)pInfo->AddressLength;i++)
        {
            byte2Hex(pInfo->Address[i],(unsigned char *)(&mac[iCount]));
            iCount+=2;
            if(i<(int)pInfo->AddressLength-1)
            {
                mac[iCount++] = ':';
            }else
            {
                mac[iCount++] = '#';
            }
			if( iCount >= 39 )
			{
				mac[39] = 0; 
				return iCount;
			}
        }
        pInfo = pInfo->Next;
    }
 
    if(iCount >0)
    {
        mac[39] = 0; 
        return 40;
    }
    else return -1;
}
#endif