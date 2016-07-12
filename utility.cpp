#include "utility.h"
 const QString Utility::tablePrefix = "t_";
 const QString Utility::wordSpliter = "_";
Utility::Utility()
{

}

Utility::~Utility()
{

}

QString Utility::tableNameConvert2ClassName(const QString &tableName)
{
	QString className = tableName.toLower();
	int i = className.indexOf(tablePrefix);
	if (i == 0)
	{
		className.remove(0, tablePrefix.length());
	}
	i = className.indexOf(wordSpliter);
	while (i >= 0)
	{
		if (className.length() > i)
		{
			className[i + 1] = className[i + 1].toUpper();
		}
		i = className.indexOf(wordSpliter,i+1);
	}
	className.remove(wordSpliter);
	if (!className.isEmpty()&&className[0].isLower())
	{
		className[0] = className[0].toUpper();
	}
	return className;
}

QString Utility::fieldNameConvert2MemberName(const QString &fieldName, const QString &className)
{
	if (fieldName.isEmpty() || className.isEmpty())
	{
		return "";
	}
	QString memberName = fieldName.toLower();
	QString filedPrefix = className[0].toLower();
	if (memberName[0] == filedPrefix[0])
	{
		memberName.remove(0, 1);
	}
	memberName = tableNameConvert2ClassName(memberName);
	return memberName;
}
