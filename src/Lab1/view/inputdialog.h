#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QSpinBox>

#include "../model/model.h"

class InputDialog : public QDialog {
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    void setParams(const GenerationParams& params);
    GenerationParams getParams() const;

private:
    QSpinBox *m_lengthSpin;
    QSpinBox *m_countSpin;
    QCheckBox *m_lowerCheck;
    QCheckBox *m_upperCheck;
    QCheckBox *m_digitsCheck;
    QCheckBox *m_symbolsCheck;
};