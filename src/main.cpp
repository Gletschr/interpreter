#include <QCoreApplication>

#include "../include/common.h"
#include "../include/variable.h"
#include "../include/std_lib.h"
#include "../include/tests.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	using namespace Interpreter;

	qDebug() << "Interpreter::benchmark(): " << benchmark();

	// 1 : 18 000 overhead
	
	return a.exec();
}
