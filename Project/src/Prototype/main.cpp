#include "ATDynamicIESApp.h"
#include <QWidget>
#include "../../src/Visualizer/ModelVisualizer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    ATDynamicIESApp a(argc, argv);
    a.getVisualazer()->show();
	return a.exec();
}
