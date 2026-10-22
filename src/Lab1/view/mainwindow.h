#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>

#include "../model/model.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    GenerationParams getLastParams() const;
    void setLastParams(const GenerationParams& params);

signals:
    void inputButtonClicked();

public slots:
    void displayPasswords(const QStringList& passwords);

private:
    QLabel *m_paramsLabel;
    QTextEdit *m_passwordsView;
    QPushButton *m_inputButton;
    GenerationParams m_lastParams;
};