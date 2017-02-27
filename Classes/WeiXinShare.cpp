//
//  WeiXinShare.cpp
//  WeiXinShare
//
//  Created by Jacky on 8/5/14.
//
//

#include "WeiXinShare.h"

WeiXinShare::WeiXinShare(){}
WeiXinShare::~WeiXinShare(){}

void WeiXinShare::sendToFriend()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo minfo;
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/MainActivity","sendMsgToFriend", "()V");
    
    if (!isHave) {
        log("jni:sendMsgToFriend is null");
    }else{
        //���ô˺���
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}

void WeiXinShare::sendToTimeLine()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo minfo;
    
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/MainActivity","sendMsgToTimeLine", "()V");
    
    if (!isHave) {
        log("jni:sendMsgToTimeLine is null");
    }else{
        //���ô˺���
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}
