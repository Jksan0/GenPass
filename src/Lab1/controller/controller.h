#pragma once

#include <QObject>

#include "../model/model.h"
#include "../view/mainwindow.h"

class AppController : public QObject {
    Q_OBJECT

public:
    AppController(PasswordModel *model, MainWindow *view, QObject *parent = nullptr);

public slots:
    void handleInputRequest();

private:
    bool validate(const GenerationParams& params, QString *error) const;

    PasswordModel *m_model;
    MainWindow *m_view;
};