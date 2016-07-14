# Generate-Model-Class-Tool
A tool which can generate model class files used by QHera via database<br>
Usage:<br>
1.Table name rule:t_ prefix,words splite by _,lower case<br>
2.Field name rule:tables' first letter as prefix，words splite by _,lower case<br>
3.When generate class name via table name,the t_ prefix will be removed and all words' first letter will be changed to upper<br>
3.Member name consist of m_[fieldName],e.g. m_nickName<br>
4.Auto make members' getter and setter functions,e.g. QString getNickName(){return m_nickName;}<br>
5.Auto make Q_PROPERTY macro,e.g. Q_PROPERTY(QString m_nickName READ getNickName WRITE setNickName)<br>
6.hera sql format
	[memberName]---->field name
	{memberName}---->memberName value
