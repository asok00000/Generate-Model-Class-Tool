#ifndef GENERATEMODELCLASS_H
#define GENERATEMODELCLASS_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QSqlField>
#include <QFile>
#include <QDesktopServices>
#include "ui_generatemodelclass.h"
#include "utility.h"
class GenerateModelClass : public QMainWindow
{
	Q_OBJECT

public:
	GenerateModelClass(QWidget *parent = 0);
	~GenerateModelClass();
private slots:
	void on_btnSelect_clicked();
	void on_btnGenerate_clicked();
private:
	Ui::GenerateModelClassClass ui;
};

#endif // GENERATEMODELCLASS_H
