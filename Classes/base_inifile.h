/********************************************************************
	history:

	created:	2013/6/06   15:22
    Filename:	base_inifile.h

    author:		lee

	purpose:	ini文件读取
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

  // 字符串替换
  std::string& StringReplace(std::string& strBig, const std::string& strsrc, const std::string& strdst);

  // 使用分割符分隔字符串
  void SplitString(const std::string& strSrc, const std::string& strFind, ArString& arSplit);
  bool saveFile( char* pFileName);
public:

  //key是等号左边的值  value是等号右边的值  
  std::map<std::string,std::string> m_Lines;
  std::string tempNil;
};
#endif    // __INIFILE_H__
