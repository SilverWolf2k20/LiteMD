#include "regex.h"

std::wregex regexHyperlink(L"[<]{1,1}(http|https|ftp:){0,1}://([^?#>]*)[>]{1,1}", std::wregex::collate);	//<http://www.url.ru>
std::wregex simplifiedRegexHyperlink(L"([<]{1,1}([^</?#>]*)[>]{1,1})", std::wregex::collate);		//<www.url.ru>
std::wregex advRegexHyperlink(L"!{0,1}\\[[^\\[\\]]*?\\]\\(.*?\\)|^\\[*?\\]\\(.*?\\)", std::wregex::collate);	//[url](����������)

std::wstring symbolCollection(L"<>[]()");		//��������� �������

//������� ������������ �������
std::wstring symbolClearanceBack(L">])");		//������� � ������
std::wstring symbolClearanceFront(L"<[(");		//������� � �����

//������� ��� �������������
std::wstring shieldingSymbolsSrc(L"`*_{}[]<>()#+-.!|/");
std::vector<std::wstring> shieldingSymbols = { 
	L"&#96;", L"&#42;", L"&#95;", L"&#123;", 
	L"&#125;", L"&#91;", L"&#93;", L"&#60;", 
	L"&#62;", L"&#40;", L"&#41;", L"&#35;", 
	L"&#43;", L"&#45;", L"&#46;", L"&#33;", 
	L"&#124;", L"&#47;" 
};

//���������� �����������
std::vector<std::wstring> replaceSymbols = { L"&#60;", L"&#62;" };

//������ ��� HTML
std::vector<std::wstring> basicUrlWrap = { L"<A HREF=\"", L"\">", L"</A>"};
std::vector<std::wstring> advUrlWrap = { L"<A HREF=\"", L"\">", L"</A>" };
