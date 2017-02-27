#include <stdio.h>
#include <android/log.h>
#include "org_cocos2dx_cpp_jniInterface.h"
#include "SocketControl.h"
#include "LevelBaseScene.h"

using namespace std;
typedef unsigned char BYTE;
char g_mac[40] ;

#define LOG_TAG "JniInterface"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
/*
 * Class:     org_cocos2dx_cpp_jniInterface
 * Method:    setJniInterfaceToDll
 * Signature: (Lorg/cocos2dx/cpp/jniInterface;)V
 */


jobject jniJava = NULL;
jobject g_context = NULL;
SOCKET_CONTRL control;

JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniInterface_setJniInterfaceToDll(
		JNIEnv *env, jobject obj, jobject jobj , jobject cont) {
	LOGD("Java_org_cocos2dx_cpp_jniInterface_setJniInterfaceToDll");

	jniJava = (jobject)(env->NewGlobalRef(jobj));
	g_context = (jobject)(env->NewGlobalRef(cont));

	getMac( env, g_mac);

	return;
}

/*
 * Class:     org_cocos2dx_cpp_jniInterface
 * Method:    recieveRomoteData
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniInterface_recieveRomoteData(
		JNIEnv *env, jobject obj, jbyteArray arr) {
	LOGD("Java_org_cocos2dx_cpp_jniInterface_recieveRomoteData");
	jsize len = env->GetArrayLength(arr);
	jbyte *jbarray = (jbyte *) malloc(len * sizeof(jbyte));
	env->GetByteArrayRegion(arr, 0, len, jbarray);
	char *dDate = (char*) jbarray;

	jint dataLen = byteToInt(dDate, 0);
	jint uid = byteToInt(dDate, 4);
	jint tid = byteToInt(dDate, 8);
	SOCKET_DATA_TYPE type;
	if(tid == 0) type = SOCKET_DATA_TYPE_INVALID;
	else if(tid == 1) type = SOCKET_DATA_TYPE_MOUSE_CONTROL;
	else if(tid == 2) type = SOCKET_DATA_TYPE_CLICK;
	else if(tid == 3) type = SOCKET_DATA_TYPE_GAME_OVER;
	jint xp = byteToInt(dDate, 12);
	jint yp = byteToInt(dDate, 16);
	gamedate date = {dataLen, {uid, type, {xp, yp}}};
	control.GameDataHandleF(date, 20);
	return;
}

void generateValidFile();
JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_jniInterface_payResult(
		JNIEnv *env, jobject obj, jint handleSharkCode , jint result )
{
	if( result == 0 )
	{
		generateValidFile();
		LevelBaseScene::resumeGame();
	}
}


jobject getJniObject()
{
	//1. 获取object静态对象
	JniMethodInfo minfo;

	bool isHave = JniHelper::getStaticMethodInfo(minfo,
												 "org/cocos2dx/cpp/jniInterface",
												 "getInstanceObj",
												 "()Ljava/lang/Object;");
	jobject activityObj = NULL;
	if (isHave)
	{
		//调用静态函数getJavaObject，获取java类对象。
		activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}

	return activityObj;
}

void sendDataToRemote(char* pData, int dataLen) { //send to java
	LOGD("sendDataToRemote:%s", pData);

	jobject activityObj = NULL;

	JniMethodInfo minfo;

	activityObj = getJniObject();

	//2. 查找displayWebView接口，获取其函数信息，并用jobj调用
	 bool isHave = JniHelper::getMethodInfo(minfo,"org/cocos2dx/cpp/jniInterface","sendDataToRemote", "([B)V");

	if (!isHave)
	{
		LOGD("jni:sendDataToRemote 函数不存在");
	}
	else
	{
		jbyteArray jbarray = minfo.env->NewByteArray(dataLen);
		BYTE byteData[512];
		for(int i=0; i< dataLen; i++) {
			byteData[i] = pData[i];
		}
		jbyte *jb=(jbyte*) byteData;
		minfo.env->SetByteArrayRegion(jbarray, 0, dataLen, jb);
		minfo.env->CallVoidMethod(activityObj, minfo.methodID, jbarray );
	}

	/*
	if (jniJava) {
		LOGD("sendDataToRemote");
		jbyteArray jbarray = jniEnv->NewByteArray(dataLen);
		BYTE byteData[512];
		for(int i=0; i< dataLen; i++) {
			byteData[i] = pData[i];
		}
		jbyte *jb=(jbyte*) byteData;
		jniEnv->SetByteArrayRegion(jbarray, 0, dataLen, jb);
		jclass cls = jniEnv->GetObjectClass(jniJava);
		jmethodID jmid = jniEnv->GetMethodID(cls, "sendDataToRemote", "([B)V");
		jniEnv->CallVoidMethod(jniJava, jmid, jbarray);
		return;
	} else {
		return;
	}
	*/
}

void callJavaStartToPay( int handleSharkCode ) { //send to java
	LOGD("callJavaStartToPay ");

	jobject activityObj = NULL;

		JniMethodInfo minfo;

		activityObj = getJniObject();

		//2. 查找接口，获取其函数信息，并用jobj调用
		 bool isHave = JniHelper::getMethodInfo(minfo,"org/cocos2dx/cpp/jniInterface","cocosRquestToPay", "(I)V");

		if (!isHave)
		{
			LOGD("jni:cocosRquestToPay 函数不存在");
		}
		else
		{

			minfo.env->CallVoidMethod(activityObj, minfo.methodID, handleSharkCode );
		}
}


jint byteToInt(char *bytes, int i) {
	int number = bytes[i] & 0xFF;
			number |= ((bytes[i+1] << 8) & 0xFF00);
			number |= ((bytes[i+2] << 16) & 0xFF0000);
			number |= ((bytes[i+3] << 24) & 0xFF000000);
	return number;
}

/*
 * 获取WifiManager 对象
 * 参数： jCtxObj 为Context对象
 */
jobject getWifiManagerObj( JNIEnv *env, jobject jCtxObj )
{
	LOGD("gotWifiMangerObj ");
    //获取 Context.WIFI_SERVICE 的值
    //jstring  jstr_wifi_serveice = env->NewStringUTF("wifi");
    jclass jCtxClz= env->FindClass("android/content/Context");
    jfieldID fid_wifi_service = env->GetStaticFieldID(jCtxClz,"WIFI_SERVICE","Ljava/lang/String;");
    jstring  jstr_wifi_serveice = (jstring)env->GetStaticObjectField(jCtxClz,fid_wifi_service);

    jclass jclz = env->GetObjectClass(jCtxObj);
    jmethodID  mid_getSystemService = env->GetMethodID(jclz,"getSystemService","(Ljava/lang/String;)Ljava/lang/Object;");
    jobject wifiManager = env->CallObjectMethod(jCtxObj,mid_getSystemService,jstr_wifi_serveice);

    //因为jclass 继承自 jobject，所以需要释放；
    //jfieldID、jmethodID是内存地址，这段内存也不是在我们代码中分配的，不需要我们来释放。
    env->DeleteLocalRef(jCtxClz);
    env->DeleteLocalRef(jclz);
    env->DeleteLocalRef(jstr_wifi_serveice);

    return wifiManager;
}

/*
 * 获取WifiInfo 对象
 * 参数： wifiMgrObj 为WifiManager对象
 */
jobject getWifiInfoObj(JNIEnv *env, jobject wifiMgrObj)
{
    LOGD("getWifiInfoObj ");
    if(wifiMgrObj == NULL){
        return NULL;
    }
    jclass jclz = env->GetObjectClass(wifiMgrObj);
    jmethodID mid = env->GetMethodID(jclz,"getConnectionInfo","()Landroid/net/wifi/WifiInfo;");
    jobject wifiInfo = env->CallObjectMethod(wifiMgrObj,mid);

    env->DeleteLocalRef(jclz);
    return wifiInfo;
}

void getMacAddress(JNIEnv *env, jobject wifiInfoObj , char mac[40] )
{
    LOGD("getMacAddress.... ");
    if(wifiInfoObj == NULL){
        return ;
    }
    jclass jclz = env->GetObjectClass(wifiInfoObj);
    jmethodID mid = env->GetMethodID(jclz,"getMacAddress","()Ljava/lang/String;");
    jstring jstr_mac = (jstring)env->CallObjectMethod(wifiInfoObj,mid);
    if(jstr_mac == NULL){
        env->DeleteLocalRef(jclz);
        return ;
    }

    const char* tmp = env->GetStringUTFChars(jstr_mac, NULL);
    memcpy(mac,tmp,strlen(tmp)+1);
    env->ReleaseStringUTFChars(jstr_mac, tmp);
    env->DeleteLocalRef(jclz);
    
     mac[39] = 0; // char* shuld be end of 0/
    return ;
}

void getMacInternal(char macOut[40])
{
	memcpy( macOut,g_mac, 40 );
}
int getMac( void *env , char mac[40] )
{
	JNIEnv *jniENV = (JNIEnv*)env;

	if( ( jniJava != NULL ) && ( g_context != NULL ) )
	{

		jobject wifiManagerObj = getWifiManagerObj(jniENV, g_context );
		jobject wifiInfoObj = getWifiInfoObj(jniENV,wifiManagerObj);
		getMacAddress(jniENV,wifiInfoObj ,mac );
		return 0;
	}

	return -1;

}

