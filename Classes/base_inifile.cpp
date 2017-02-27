/********************************************************************
history:

created:	2013/6/06   15:22
Filename:	base_inifile.cpp

author:		lee

purpose:	ini�ļ���ȡ
comment:    
*********************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include "base_inifile.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;
static CIniFile* share=NULL;
//-----------------------------------------------------------------------------
CIniFile* CIniFile::toIns()
{
  if(!share){  
    share = new CIniFile();  
    CCLOG("first");  
  }  
  //CCLOG("hello");  
  return share;  
}
//-----------------------------------------------------------------------------
CIniFile::CIniFile(void)
{
}
//-----------------------------------------------------------------------------
CIniFile::~CIniFile(void)
{
}
//-----------------------------------------------------------------------------
bool CIniFile::Init(const char* pCfgFilePath)
{
  bool bRet = false;
  tempNil = "";

  unsigned char* pBuffer = NULL;
  ssize_t bufferSize = 0;
  string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pCfgFilePath;  
  pBuffer = CCFileUtils::sharedFileUtils()->getFileData( path , "r", &bufferSize);

  if (pBuffer)
  {
    int nLineLength = 0;
    string lineStr="";
    for(unsigned long i = 0; i < bufferSize; i ++)
    {
      if(pBuffer[i] != '\r' && pBuffer[i] !='\n' && pBuffer[i] !='\0')
      {
        lineStr += pBuffer[i];
        nLineLength ++;
      }
      else
      {
        if(nLineLength > 0)//��ȡ��һ������
        {
          StringReplace(lineStr, " ", "");
          if(lineStr.length() > 0)
          {
            ArString lineAr;
            SplitString(lineStr,"=",lineAr);
            if(lineAr.size() >= 2)
            {
              string postfix(lineAr[1]);
              if(postfix.length() > 3)
              {
                postfix = postfix.substr(postfix.size() - 3, postfix.size()); // ��ȡ�������
                if (strcmp("txt", postfix.c_str()) == 0)//�����txt·��
                {
                  lineAr[1] = m_Lines["TXTPATH"] + lineAr[1];
                }
                if (strcmp("png", postfix.c_str()) == 0)//�����txt·��
                {
                  lineAr[1] = m_Lines["IMAGEPATH"] + lineAr[1];
                }
                if (strcmp("jpg", postfix.c_str()) == 0)//�����txt·��
                {
                  lineAr[1] = m_Lines["IMAGEPATH"] + lineAr[1];
                }
              }
              m_Lines[lineAr[0]] = lineAr[1];    
            }
          }

          nLineLength = 0;
          lineStr = "";
        }
        else
          continue;
      }
    }
    bRet = true;
  }
  return bRet;
}
//-----------------------------------------------------------------------------
std::string& CIniFile::GetValue(const std::string& strKey)
{
  std::map<std::string,std::string>::iterator it = m_Lines.find(strKey);
  if(it != m_Lines.end())
    return it->second;
  else
    return tempNil;
}

void CIniFile::setValue( const std::string strKey , const std::string value )
{
	m_Lines[strKey] = value;

	
}
//-----------------------------------------------------------------------------
std::string& CIniFile::StringReplace(std::string& strBig, const std::string& strsrc, const std::string& strdst) 
{
  std::string::size_type pos = 0;
  std::string::size_type srclen = strsrc.size();
  std::string::size_type dstlen = strdst.size();
  while( (pos = strBig.find(strsrc, pos)) != std::string::npos)
  {
    strBig.replace(pos, srclen, strdst);
    pos += dstlen;
  }
  return strBig;
}

//-----------------------------------------------------------------------------
void CIniFile::SplitString(const std::string& strSrc, const std::string& strFind, ArString& arSplit)
{
  int st = 0;
  int npos = strSrc.find(strFind);
  if (npos == -1)
  {
    arSplit.push_back(strSrc);
    return;
  }

  while(npos > -1)
  {
    arSplit.push_back(strSrc.substr(st, npos - st));
    st = npos + strFind.size();
    npos = strSrc.find(strFind, npos + 1);

    if (npos <= -1)
    {
      arSplit.push_back(strSrc.substr(st, npos - st));
      break;
    }
  }
}

bool CIniFile::saveFile(  char* pFileName){  
    //��һ��ȡ������ļ�·��  
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + pFileName;  
      
    //����һ���ļ�ָ��  
    //·����ģʽ 
	
    FILE* file = fopen(path.c_str(), "w");  
    if (file) {  
        
		map<string,string>::iterator   it=m_Lines.begin();   
		for(;it!=m_Lines.end();++it)   
        {
			string context =  it->first + "=" + it->second + "\r\n";

			fputs(context.c_str(), file);  
		}
        fclose(file);
		return true;
    }  
	else
	{
		return false;  
	}
}  