#include <QtGui>

#include "ConfigPages.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include "QStationItem.h"
#include "ModelVisualizer.h"

CommonSettings::CommonSettings(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *settingsGroup = new QGroupBox(tr("Common settings"));
    QCheckBox *setting1 = new QCheckBox(tr("Ask before bandwidth resizing"));

    QVBoxLayout *settingsLayout = new QVBoxLayout;
    settingsLayout->addWidget(setting1);
    settingsGroup->setLayout(settingsLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(settingsGroup);
    mainLayout->addSpacing(12);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}



SatelliteSettings::SatelliteSettings(QVector<Satellite*> *pSatelliteList, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *satelliteChooseGroup = new QGroupBox(tr("Choose satellite"));
    QLabel *satelliteLabel = new QLabel(tr("Satellite:"));
    QComboBox *satelliteCombo = new QComboBox;
    for (QVector<Satellite*>::iterator it = pSatelliteList->begin(); it != pSatelliteList->end(); it++)
    {
        satelliteCombo->addItem((*it)->name());
    }
    QHBoxLayout *satelliteChooseLayout = new QHBoxLayout;
    satelliteChooseLayout->addWidget(satelliteLabel);
    satelliteChooseLayout->addWidget(satelliteCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(satelliteChooseLayout);
    satelliteChooseGroup->setLayout(configLayout);


    QLabel *maxBwSettingsLabel = new QLabel(tr("Maximum bandwidth:"));
    QLineEdit *maxBwSettingsLineEdit = new QLineEdit;

    QGroupBox *satelliteSettingsGroup = new QGroupBox(tr("Satellite configuration"));
    QGridLayout *satelliteSettingsLayout =  new QGridLayout;
    satelliteSettingsLayout->addWidget(maxBwSettingsLabel,0,0);
    satelliteSettingsLayout->addWidget(maxBwSettingsLineEdit,0,1);
    satelliteSettingsGroup->setLayout(satelliteSettingsLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(satelliteChooseGroup);
    mainLayout->addWidget(satelliteSettingsGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

StationSettings::StationSettings(QVector<Station*> *pStationList, QVector<Satellite*> *pSatelliteList, QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *stationChooseGroup = new QGroupBox(tr("Choose station"));
    QLabel *stationLabel = new QLabel(tr("Station:"));
    QComboBox *stationCombo = new QComboBox;
    for (QVector<Station*>::iterator it = pStationList->begin(); it != pStationList->end(); it++)
    {
        stationCombo->addItem((*it)->name());
    }
    QHBoxLayout *stationChooseLayout = new QHBoxLayout;
    stationChooseLayout->addWidget(stationLabel);
    stationChooseLayout->addWidget(stationCombo);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(stationChooseLayout);
    stationChooseGroup->setLayout(configLayout);


    QLabel *satelliteSettingsLabel = new QLabel(tr("Satellite connected to:"));
    QComboBox *satelliteSettingsCombo = new QComboBox;
    for (QVector<Satellite*>::iterator it = pSatelliteList->begin(); it != pSatelliteList->end(); it++)
    {
        satelliteSettingsCombo->addItem((*it)->name());
    }

    QLabel *callingSettingsLabel = new QLabel(tr("Calling ground connection chance:"));
    QLineEdit *callingSettingsLineEdit = new QLineEdit;

    QLabel *failureSettingsLabel = new QLabel(tr("Failure ground connection chance:"));
    QLineEdit *failureSettingsLineEdit = new QLineEdit;

    QGroupBox *stationSettingsGroup = new QGroupBox(tr("Station configuration"));
    QGridLayout *stationSettingsLayout =  new QGridLayout;
    stationSettingsLayout->addWidget(satelliteSettingsLabel,0,0);
    stationSettingsLayout->addWidget(satelliteSettingsCombo,0,1);
    stationSettingsLayout->addWidget(callingSettingsLabel,1,0);
    stationSettingsLayout->addWidget(callingSettingsLineEdit,1,1);
    stationSettingsLayout->addWidget(failureSettingsLabel,2,0);
    stationSettingsLayout->addWidget(failureSettingsLineEdit,2,1);
    stationSettingsGroup->setLayout(stationSettingsLayout);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(stationChooseGroup);
    mainLayout->addWidget(stationSettingsGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

