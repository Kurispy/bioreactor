#ifndef OD_H
#define OD_H

#include <QtWidgets>

class ODOverview : public QGroupBox
{
    Q_OBJECT
public:
    explicit ODOverview(QWidget *parent = 0);
    
signals:
    void zeroOD();
    
public slots:

private:
    QGridLayout *grid_layout_;
    QLabel *current_value_;
    QPushButton *zero_button_;
    QSlider *target_value_slider_;
    QDoubleSpinBox *target_value_spin_box_;
    
};

#endif // OD_H
