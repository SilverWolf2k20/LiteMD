#include "syntax_postprocessor.h"
#include "qstring.h"
//������ �� ������� \n
void processCRLF(QString &str)
{
	for (int i = 0;i < str.size();++i)
	{
		//���� ������� \n �� �������� html �����
		if (str[i] == '\n')
		{
			str.replace(i, 1, "<BR>");
			processCRLF(str);
		}
	}
}
