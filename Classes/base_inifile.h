/********************************************************************
	history:

	created:	2013/6/06   15:22
    Filename:	base_inifile.h

    author:		lee

	purpose:	ini�ļ���ȡ
	comment:    
  *********************************************************************/
#ifndef __INIFILE_H__
#define __INIFILE_H__

#include <string>
#include <map>
#include <vector>
#include "cocos2d.h"

typedef std::vector<std::string> ArString;
struct FileDataInfo
{
  std::string strKey;
  std::string strValue;
};

class CIniFile
{
public:
  CIniFile(void);
  ~CIniFile(void);
  static CIniFile* toIns();
  bool Init(const char* pCfgFilePath);
  std::string& GetValue(const std::string& strKey);
  void setValue( const std::string strKey , const std::string value );

  // �ַ����滻
  std::string& StringReplace(std::string& strBig, const std::string& strsrc, const std::string& strdst);

  // ʹ�÷ָ���ָ��ַ���
  void SplitString(const std::string& strSrc, const std::string& strFind, ArString& arSplit);
  bool saveFile( char* pFileName);
public:

  //key�ǵȺ���ߵ�ֵ  value�ǵȺ��ұߵ�ֵ  
  std::map<std::string,std::string> m_Lines;
  std::string tempNil;
};
#endif    // __INIFILE_H__
