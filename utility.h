#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
class Utility
{
public:
	Utility();
	~Utility();
	const static  QString tablePrefix;
	const static  QString wordSpliter;
	static QString tableNameConvert2ClassName(const QString &tableName);
	static QString fieldNameConvert2MemberName(const QString &fieldName, const QString &className);
private:
	
};

#endif // UTILITY_H
