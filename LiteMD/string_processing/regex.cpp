#include "regex.h"

std::wregex regexHyperlink(L"[<]{1,1}(http|https|ftp:){0,1}://([^/?#>]*)[>]{1,1}", std::wregex::collate);	//<http://www.url.ru>
std::wregex simplifiedRegexHyperlink(L"[<]{1,1}([^</?#>]*)[>]{1,1}", std::wregex::collate);	//<www.url.ru>
std::wregex advRegexHyperlink(L"(\\[(.*?)\\])(\\(\\S{1,})\\)", std::wregex::collate);	//[url](����������)

std::wstring symbolCollection(L"<>[]()");		//��������� �������

//������� ������������ �������
std::wstring symbolClearanceBack(L">])");		//������� � ������
std::wstring symbolClearanceFront(L"<[(");		//������� � �����

//���������� �����������
std::vector<std::wstring> replaceSymbols = { L"&#60;", L"&#62;" };

//������ ��� HTML
std::vector<std::wstring> basicUrlWrap = { L"<A HREF=\"", L"\">", L"</A>"};
std::vector<std::wstring> advUrlWrap = { L"<A HREF=\"", L"\">", L"</A>" };
