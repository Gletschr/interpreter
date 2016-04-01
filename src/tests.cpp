#include "../include/tests.h"

#include <QElapsedTimer>

namespace Interpreter {

	//-------------------------------------------------------------------------

	bool benchmark() {

		try {

			QElapsedTimer timer;

			timer.start();
			for(int i = 0; i < 500000; ++ i) {}
			quint64 time = timer.elapsed();
			qDebug() << "C++: " << time;

			Variable size(500000);

			timer.start();
			for(Variable it = Variable(0); (bool &)(it < size); ++it) {}
			time = timer.elapsed();
			qDebug() << "Interpreter: " << time;

		return true;

		} catch(const char *ex) {
			qDebug() << ex;
		}

		return false;
	}

	//-------------------------------------------------------------------------

}
