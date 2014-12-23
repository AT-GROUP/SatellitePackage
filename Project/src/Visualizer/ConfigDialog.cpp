#include <QtGui>

#include "ConfigDialog.h"
#include "ConfigPages.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

ConfigDialog::ConfigDialog(QVector<Station*> *pStationList, QVector<Satellite*> *pSatelliteList, QWidget* parent)
{
    Q_UNUSED(parent);

    pContentsWidget = new QListWidget;
    pContentsWidget->setViewMode(QListView::IconMode);
    pContentsWidget->setIconSize(QSize(96, 84));
    pContentsWidget->setMovement(QListView::Static);
    pContentsWidget->setMaximumWidth(128);
    pContentsWidget->setSpacing(12);
    pContentsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    pPagesWidget = new QStackedWidget;
    pPagesWidget->addWidget(new CommonSettings());
    pPagesWidget->addWidget(new SatelliteSettings(pSatelliteList));
    pPagesWidget->addWidget(new StationSettings(pStationList, pSatelliteList));
    pPagesWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPushButton *closeButton = new QPushButton(tr("Apply and close"));

    createIcons();
    pContentsWidget->setCurrentRow(0);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(pContentsWidget);
    horizontalLayout->addWidget(pPagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    //buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    //mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
    resize(600,400);
}

void ConfigDialog::createIcons()
{
    QListWidgetItem *commonConfigButton = new QListWidgetItem(pContentsWidget);
    commonConfigButton->setIcon(QIcon(":settings"));
    commonConfigButton->setText(tr("Configuration"));
    commonConfigButton->setTextAlignment(Qt::AlignHCenter);
    commonConfigButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *satellitesButton = new QListWidgetItem(pContentsWidget);
    satellitesButton->setIcon(QIcon(":satellite"));
    satellitesButton->setText(tr("Satellites"));
    satellitesButton->setTextAlignment(Qt::AlignVCenter);
    satellitesButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *stationsButton = new QListWidgetItem(pContentsWidget);
    stationsButton->setIcon(QIcon(":station"));
    stationsButton->setText(tr("Stations"));
    stationsButton->setTextAlignment(Qt::AlignHCenter);
    stationsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(pContentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pPagesWidget->setCurrentIndex(pContentsWidget->row(current));
}
