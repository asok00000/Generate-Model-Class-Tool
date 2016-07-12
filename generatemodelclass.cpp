#include "generatemodelclass.h"

GenerateModelClass::GenerateModelClass(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

GenerateModelClass::~GenerateModelClass()
{

}

void GenerateModelClass::on_btnSelect_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"",	QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty() && QDir(dir).exists())
	{
		ui.txtPath->setText(dir);
	}
}

void GenerateModelClass::on_btnGenerate_clicked()
{
	QSqlDatabase database = QSqlDatabase::addDatabase(ui.cbxDriverType->currentText());
	database.setDatabaseName(ui.txtDbName->text());
	database.setConnectOptions(ui.txtConnOpt->text());
	database.setHostName(ui.txtHostName->text());
	database.setPassword(ui.txtPwd->text());
	database.setPort(ui.txtPort->text().toInt());
	database.setUserName(ui.txtUserName->text());
	QString dirPath = ui.txtPath->text();
	if (!database.open())
	{
		qDebug() << database.lastError();
		//return result;
	}
	QStringList tables = database.tables();
	foreach(QString table, tables)
	{
		QSqlRecord record = database.record(table);
		QString className =  Utility::tableNameConvert2ClassName(table);
		QFile hFile(dirPath+QDir::separator() + className.toLower() + ".h");
		QString header = "#ifndef %1_H\n#define %1_H\n#include <QObject>\nclass %2 : public QObject\n{\n    Q_OBJECT\n";
		header = header.arg(className.toUpper()).arg(className);
		QString propertyDecl = "", propertyGeterAndSetter = "",members="";
		QString footer = "\n};\n#endif";
		if (hFile.open(QIODevice::WriteOnly))
		{
			QString propertyTemp = "    Q_PROPERTY(%1 m_%2 READ get%3 WRITE set%3)";
			QString getterTemp = "    %1 get%2() const\n    {\n        return m_%3;\n    }";
			QString setterTemp = "    void set%2(%1 val)\n    {\n        m_%3 = val;\n    }";
			QString memberTemp = "    %1 m_%2;";
			for (int i = 0; i < record.count(); ++i) 
			{
				QString fieldName = Utility::fieldNameConvert2MemberName(record.field(i).name(), className);
				QString memberName = Utility::fieldNameConvert2MemberName(record.field(i).name(), className).replace(0,1, fieldName[0].toLower());
				QString fieldType = record.field(i).value().typeName();
				propertyDecl += propertyTemp.arg(fieldType, memberName, fieldName);
				propertyDecl += "\n";
				propertyGeterAndSetter += getterTemp.arg(fieldType, fieldName, memberName);
				propertyGeterAndSetter += "\n";
				propertyGeterAndSetter += setterTemp.arg(fieldType, fieldName, memberName);
				propertyGeterAndSetter += "\n";
				members += memberTemp.arg(fieldType).arg(memberName);
				members += "\n";
			}
			hFile.write(header.toUtf8());
			hFile.write(propertyDecl.toUtf8());
			hFile.write("public:\n");
			hFile.write(propertyGeterAndSetter.toUtf8());
			hFile.write("private:\n");
			hFile.write(members.toUtf8());
			hFile.write(footer.toUtf8());
			hFile.close();
		}
		else
		{
			qDebug() << "create file error."<<hFile.errorString();
		}
	}
	database.close();
	QDesktopServices::openUrl(dirPath);
}
