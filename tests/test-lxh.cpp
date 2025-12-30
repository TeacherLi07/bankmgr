#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using std::cin, std::cout, std::endl;

// 复制 Sort.h 中的逻辑进行调试
std::wstring toWString(const std::string& str) {
    if (str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

void test_compare_with_lcid(const std::string& name1, const std::string& name2, DWORD lcid, const std::string& desc) {
    std::wstring s1 = toWString(name1);
    std::wstring s2 = toWString(name2);
    
    int result = CompareStringW(lcid, 0, s1.c_str(), -1, s2.c_str(), -1);
    
    cout << "Comparing " << name1 << " and " << name2 << " with " << desc << " (0x" << std::hex << lcid << std::dec << "): ";
    if (result == CSTR_LESS_THAN) cout << "LESS";
    else if (result == CSTR_EQUAL) cout << "EQUAL";
    else if (result == CSTR_GREATER_THAN) cout << "GREATER";
    else cout << "ERROR " << GetLastError();
    cout << endl;
}

int main()
{
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);
    
    cout << "Debug Sorting..." << endl;
    
    // Pinyin order: Chen (陈) < Wang (王) < Xiao (小)
    // So:
    // Chen < Xiao -> LESS
    // Xiao > Wang -> GREATER
    
    test_compare_with_lcid("陈思", "小灰灰", 0x0804, "Default zh-CN");
    test_compare_with_lcid("陈思", "小灰灰", 0x00020804, "Pinyin");
    test_compare_with_lcid("陈思", "小灰灰", 0x00030804, "Stroke");
    
    cout << "----------------" << endl;
    
    test_compare_with_lcid("小灰灰", "王芳", 0x0804, "Default zh-CN");
    test_compare_with_lcid("小灰灰", "王芳", 0x00020804, "Pinyin");
    test_compare_with_lcid("小灰灰", "王芳", 0x00030804, "Stroke");

    return 0;
}