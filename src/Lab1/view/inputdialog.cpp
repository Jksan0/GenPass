#include "inputdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QStyle>
#include <QVBoxLayout>

namespace {
void updateLimitProperties(QSpinBox *spinBox) {
    const bool atMinimum = spinBox->value() == spinBox->minimum();
    const bool atMaximum = spinBox->value() == spinBox->maximum();
    const bool changed = spinBox->property("atMinimum").toBool() != atMinimum
        || spinBox->property("atMaximum").toBool() != atMaximum;

    if (!changed) {
        return;
    }

    spinBox->setProperty("atMinimum", atMinimum);
    spinBox->setProperty("atMaximum", atMaximum);
    spinBox->style()->unpolish(spinBox);
    spinBox->style()->polish(spinBox);
    spinBox->update();
}
}

InputDialog::InputDialog(QWidget *parent)
    : QDialog(parent),
      m_lengthSpin(new QSpinBox(this)),
      m_countSpin(new QSpinBox(this)),
      m_lowerCheck(new QCheckBox("Строчные буквы (a-z)", this)),
      m_upperCheck(new QCheckBox("Заглавные буквы (A-Z)", this)),
      m_digitsCheck(new QCheckBox("Цифры (0-9)", this)),
      m_symbolsCheck(new QCheckBox("Спецсимволы (!@#)", this)) {
    setWindowTitle("Параметры паролей");

    m_lengthSpin->setRange(1, MaxPasswordLength);
    m_countSpin->setRange(1, 100);
        connect(m_lengthSpin, qOverload<int>(&QSpinBox::valueChanged),
            this, [this](int) { updateLimitProperties(m_lengthSpin); });
        connect(m_countSpin, qOverload<int>(&QSpinBox::valueChanged),
            this, [this](int) { updateLimitProperties(m_countSpin); });
        updateLimitProperties(m_lengthSpin);
        updateLimitProperties(m_countSpin);

    auto *formLayout = new QFormLayout;
    formLayout->addRow("Длина пароля:", m_lengthSpin);
    formLayout->addRow("Количество паролей:", m_countSpin);

    auto *setsLayout = new QVBoxLayout;
    setsLayout->addWidget(m_lowerCheck);
    setsLayout->addWidget(m_upperCheck);
    setsLayout->addWidget(m_digitsCheck);
    setsLayout->addWidget(m_symbolsCheck);

    auto *setsGroup = new QGroupBox("Использовать символы", this);
    setsGroup->setLayout(setsLayout);

    auto *buttons = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(setsGroup);
    layout->addWidget(buttons);
}

void InputDialog::setParams(const GenerationParams& params) {
    m_lengthSpin->setValue(params.length);
    m_countSpin->setValue(params.count);
    m_lowerCheck->setChecked(params.useLower);
    m_upperCheck->setChecked(params.useUpper);
    m_digitsCheck->setChecked(params.useDigits);
    m_symbolsCheck->setChecked(params.useSymbols);
}

GenerationParams InputDialog::getParams() const {
    GenerationParams params;
    params.length = m_lengthSpin->value();
    params.count = m_countSpin->value();
    params.useLower = m_lowerCheck->isChecked();
    params.useUpper = m_upperCheck->isChecked();
    params.useDigits = m_digitsCheck->isChecked();
    params.useSymbols = m_symbolsCheck->isChecked();
    return params;
}