#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSizePolicy>

class Control : public QWidget
{

private:

    QWidget *tab_pump;
    QWidget *tab_control;
    QTabWidget *tabWidget;
    QVBoxLayout *layout;

public:
    Control(QWidget *parent = 0): QWidget(parent)
    {

    }
    void setup()
    {

        tabWidget = new QTabWidget(this);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setDocumentMode(false);

        tab_pump = new QWidget();
        tab_pump->setObjectName(QStringLiteral("tab_pump"));

        layout = new QVBoxLayout(tab_pump);

		makePumpControls(tab_pump,1,layout);
		makePumpControls(tab_pump,2,layout);

        tab_control = new QWidget();
        tab_control->setObjectName(QStringLiteral("tab_control"));

        tabWidget->addTab(tab_pump,QString());
        tabWidget->addTab(tab_control,QString());
        tabWidget->setCurrentIndex(0);

        tabWidget->setTabText(tabWidget->indexOf(tab_pump), "Tab pump");
        tabWidget->setTabText(tabWidget->indexOf(tab_control), "Tab control");
    }

	void makePumpControls(QWidget *parent, int num, QVBoxLayout *layout)
	{
		QHBoxLayout *Hlayout = new QHBoxLayout();
		QLabel *labelPump = new QLabel(parent);
		QLineEdit *lineEdit = new QLineEdit(parent);
		QLabel *labelRPM = new QLabel(parent);
		QSpinBox *spinBox = new QSpinBox(parent);
		QLabel *labelDirection = new QLabel(parent);
		QPushButton *buttonDirection = new QPushButton(parent);
		QSlider *slider = new QSlider(parent);
		slider->setOrientation(Qt::Horizontal);

		labelPump->setText(QString("Pump %1").arg(num));
		labelRPM->setText(QString("RPM"));

		labelDirection->setText(QString("Direction"));
		buttonDirection->setText("Direction");

		Hlayout->addWidget(labelPump);
		Hlayout->addWidget(lineEdit);

  		layout->addLayout(Hlayout);

		Hlayout = new QHBoxLayout();
		Hlayout->addWidget(labelRPM);
		Hlayout->addWidget(slider);
		Hlayout->addWidget(spinBox);

		layout->addLayout(Hlayout);

		Hlayout = new QHBoxLayout();
		Hlayout->addWidget(labelDirection);
		Hlayout->addWidget(buttonDirection);

		layout->addLayout(Hlayout);

		connect(slider, SIGNAL(sliderMoved(int)), spinBox, SLOT(setValue(int)));
		connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));

	}

};
#endif
