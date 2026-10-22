#include "controller.h"

#include "../view/inputdialog.h"

#include <QMessageBox>

AppController::AppController(PasswordModel *model, MainWindow *view, QObject *parent)
    : QObject(parent), m_model(model), m_view(view) {
    connect(m_view, &MainWindow::inputButtonClicked,
            this, &AppController::handleInputRequest);
}

void AppController::handleInputRequest() {
    InputDialog dialog(m_view);
    dialog.setParams(m_view->getLastParams());

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    const GenerationParams params = dialog.getParams();
    m_view->setLastParams(params);

    QString error;
    if (!validate(params, &error)) {
        QMessageBox::critical(m_view, "Ошибка ввода", error);
        return;
    }

    m_model->generate(params);
}

bool AppController::validate(const GenerationParams& params, QString *error) const {
    if (params.length <= 0 || params.count <= 0) {
        *error = "Длина и количество паролей должны быть больше нуля.";
        return false;
    }

    if (params.length > MaxPasswordLength) {
        *error = QString("Максимальная длина пароля — %1 символов.")
            .arg(MaxPasswordLength);
        return false;
    }

    const int selectedSets = static_cast<int>(params.useLower)
        + static_cast<int>(params.useUpper)
        + static_cast<int>(params.useDigits)
        + static_cast<int>(params.useSymbols);

    if (selectedSets == 0) {
        *error = "Выберите хотя бы один набор символов.";
        return false;
    }

    if (params.length < selectedSets) {
        *error = "Длина пароля должна быть не меньше количества выбранных наборов символов.";
        return false;
    }

    return true;
}