#include "generatemodelclass.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GenerateModelClass w;
	w.show();
	return a.exec();
}
