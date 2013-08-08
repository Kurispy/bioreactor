#include "OD.h"

ODOverview::ODOverview(QWidget *parent) :
    QGroupBox(parent)
{
    setTitle("OD");

    grid_layout_ = new QGridLayout(this);
    current_value_ = new QLabel("0");
    zero_button_ = new QPushButton("Zero OD");
    target_value_slider_ = new QSlider(Qt::Vertical);
    target_value_spin_box_ = new QDoubleSpinBox();

    grid_layout_->addWidget(current_value_, 0, 0, 2, 1, Qt::AlignCenter);
    grid_layout_->addWidget(zero_button_, 3, 0, Qt::AlignCenter);
    grid_layout_->addWidget(target_value_slider_, 1, 1, 2, 1, Qt::AlignCenter);
    grid_layout_->addWidget(target_value_spin_box_, 3, 1, Qt::AlignCenter);

    setLayout(grid_layout_);
    setStyleSheet("QGroupBox { border: 1px solid gray; margin-top: 0.5em;} QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px; }");
}
