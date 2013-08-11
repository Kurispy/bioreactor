#ifndef UI_MONITOR_H
#define UI_MONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

class Monitor : public QWidget
{

	friend MainWidget;

private:

    QLCDNumber *lcd_pump1;
    QLCDNumber *lcd_DO;
    QLCDNumber *lcd_pump2;
    QLCDNumber *lcd_OD;
    QLCDNumber *lcd_temp;
    QLCDNumber *lcd_pH;

    QLabel *label_MONITOR;
    QLabel *label_pH;
    QLabel *label_temp;
    QLabel *label_DO;
    QLabel *label_OD;
    QLabel *label_pump1;
    QLabel *label_pump2;

    QGridLayout *layout_main;

public:

    Monitor(QWidget *parent = 0) : QWidget(parent)
    {

    }

    void setup()
    {
//		LABELS
        label_MONITOR = new QLabel(this);
        label_MONITOR->setObjectName(QStringLiteral("label_MONITOR"));

        QFont font;
        font.setPointSize(16);
        label_MONITOR->setFont(font);

        label_pH = new QLabel(this);
        label_pH->setObjectName(QStringLiteral("label_pH"));
        label_pH->setText("pH");
        label_temp = new QLabel(this);
        label_temp->setObjectName(QStringLiteral("label_temp"));
        label_temp->setText("Temperature");
        label_OD = new QLabel(this);
        label_OD->setObjectName(QStringLiteral("label_OD"));
        label_OD->setText("Optical Density");
        label_DO = new QLabel(this);
        label_DO->setObjectName(QStringLiteral("label_DO"));
        label_DO->setText("Dissolve Oxygen");
        label_pump1 = new QLabel(this);
        label_pump1->setObjectName(QStringLiteral("label_pump1"));
        label_pump1->setText("Pump 1 RPM");
        label_pump2 = new QLabel(this);
        label_pump2->setObjectName(QStringLiteral("lablel_pump2"));
        label_pump2->setText("Pump 2 RPM");

//  	LCD
        lcd_temp = new QLCDNumber(this);
        lcd_temp->setObjectName(QStringLiteral("lcd_temp"));
        lcd_temp->setEnabled(true);
        lcd_temp->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                              "color: rgb(85, 255, 0);"));
        lcd_temp->setSmallDecimalPoint(false);
        lcd_temp->setSegmentStyle(QLCDNumber::Flat);
        lcd_temp->setProperty("value", QVariant(0.34));

        lcd_pH = new QLCDNumber(this);
        lcd_pH->setObjectName(QStringLiteral("lcd_pH"));
        lcd_pH->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                            "color: rgb(85, 255, 0);"));
        lcd_pH->setSegmentStyle(QLCDNumber::Flat);

        lcd_OD = new QLCDNumber(this);
        lcd_OD->setObjectName(QStringLiteral("lcd_OD"));
        lcd_OD->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                            "color: rgb(85, 255, 0);"));
        lcd_OD->setSegmentStyle(QLCDNumber::Flat);

        lcd_DO = new QLCDNumber(this);
        lcd_DO->setObjectName(QStringLiteral("lcd_DO"));
        lcd_DO->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                            "color: rgb(85, 255, 0);"));
        lcd_DO->setSegmentStyle(QLCDNumber::Flat);

        lcd_pump1 = new QLCDNumber(this);
        lcd_pump1->setObjectName(QStringLiteral("lcd_pump1"));
        lcd_pump1->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                               "color: rgb(85, 255, 0);"));
        lcd_pump1->setSegmentStyle(QLCDNumber::Flat);

        lcd_pump2 = new QLCDNumber(this);
        lcd_pump2->setObjectName(QStringLiteral("lcd_pump2"));
        lcd_pump2->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
                                               "color: rgb(85, 255, 0);"));
        lcd_pump2->setSegmentStyle(QLCDNumber::Flat);

//		LAYOUT
        layout_main = new QGridLayout();
        layout_main->setSpacing(6);
        layout_main->setContentsMargins(11, 11, 11, 11);
        layout_main->setObjectName(QStringLiteral("layout_main"));
        layout_main->addWidget(label_MONITOR, 0, 5, 1, 1);
        layout_main->addWidget(label_pH, 3, 1, 1, 1);
        layout_main->addWidget(lcd_pH, 3, 2, 1, 1);
        layout_main->addWidget(label_temp, 5, 1, 1, 1);
        layout_main->addWidget(lcd_temp, 5, 2, 1, 1);
        layout_main->addWidget(label_OD, 3, 5, 1, 1);
        layout_main->addWidget(lcd_OD, 3, 6, 1, 1);
        layout_main->addWidget(label_DO, 5, 5, 1, 1);
        layout_main->addWidget(lcd_DO, 5, 6, 1, 1);
        layout_main->addWidget(label_pump1, 3, 8, 1, 1);
        layout_main->addWidget(lcd_pump1, 3, 9, 1, 1);
        layout_main->addWidget(label_pump2, 5, 8, 1, 1);
        layout_main->addWidget(lcd_pump2, 5, 9, 1, 1);

        this->setLayout(layout_main);
    }
};

#endif
