#include <stdio.h>
#include <SystemConfiguration/SCPreferences.h>

void dumpDict(CFDictionaryRef dict) {
	//讲字典导出到XML格式简单粗暴的方式
	CFDataRef xml = CFPropertyListCreateXMLData(kCFAllocatorDefault, (CFPropertyListRef)dict);

	if (xml) {
		write(1, CFDataGetBytePtr(xml), CFDataGetLength(xml));
		CFRelease(xml);
	}
}

void main(int argc, char **argv)
{
	CFStringRef myName = CFSTR("com.technologeeks.SystemConfigurationTest");
	CFArrayRef keyList;
	SCPreferencesRef prefs = NULL;
	char *val;
	CFIndex i;
	CFDictionaryRef global;

	//打开一个选项配置的回话
	prefs = SCPreferencesCreate(NULL, myName, NULL);

	if (!prefs)	{fprintf(stderr, "SCPreferencesCreate failed\n"); exit(1); }

	//获取选项配置的名称空间
	keyList = SCPreferencesCopyKeyList(prefs);	

	if (!keyList) {fprintf(stderr, "CopyKeyList failed \n"); exit(2); }

	//导出
	for (i = 0; i < CFArrayGetCount(keyList); ++i) {
		dumpDict(SCPreferencesGetValue(prefs, CFArrayGetValueAtIndex(keyList, i)));
	}

}