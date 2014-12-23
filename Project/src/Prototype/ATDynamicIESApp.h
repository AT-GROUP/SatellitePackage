#ifndef ATDYNAMICPROTOTYPE_ATDynamicIESApp_H
#define ATDYNAMICPROTOTYPE_ATDynamicIESApp_H

#include <QtWidgets/QApplication>

class Wrapper;
class QTimer;
class ModelVisualizer;

class ATDynamicIESApp: public QApplication
{
	Q_OBJECT
	public:
        ATDynamicIESApp(int & argc ,char** argv);
		~ATDynamicIESApp();
        ModelVisualizer* getVisualazer();
	private:
		QTimer *pTickTimer;
        Wrapper *pWrapper;
        ModelVisualizer *pVisualizer;
		int state;

	public slots:
		virtual void reachNextState();
};
	
#endif
