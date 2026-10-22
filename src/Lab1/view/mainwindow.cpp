#include "mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_paramsLabel(new QLabel("Последние параметры не заданы.", this)),
      m_passwordsView(new QTextEdit(this)),
      m_inputButton(new QPushButton("Ввести данные", this)) {
    setWindowTitle("Генератор паролей");
        resize(600, 500);

        auto *pageTitle = new QLabel("Генератор паролей", this);
        pageTitle->setObjectName("pageTitle");
        m_paramsLabel->setObjectName("paramsPanel");
        m_paramsLabel->setWordWrap(true);

        auto *resultsTitle = new QLabel("Сгенерированные пароли", this);
        resultsTitle->setObjectName("sectionTitle");
    m_passwordsView->setReadOnly(true);
    m_passwordsView->setPlaceholderText("Сгенерированные пароли появятся здесь.");
        m_passwordsView->setObjectName("passwordsView");
        m_inputButton->setObjectName("primaryButton");

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);
        layout->setContentsMargins(28, 26, 28, 26);
        layout->setSpacing(16);
        layout->addWidget(pageTitle);
    layout->addWidget(m_paramsLabel);
        layout->addWidget(resultsTitle);
    layout->addWidget(m_passwordsView, 1);
    layout->addWidget(m_inputButton);
    setCentralWidget(centralWidget);

    connect(m_inputButton, &QPushButton::clicked,
            this, &MainWindow::inputButtonClicked);
}

GenerationParams MainWindow::getLastParams() const {
    return m_lastParams;
}

void MainWindow::setLastParams(const GenerationParams& params) {
    m_lastParams = params;

    QStringList selectedSets;
    if (params.useLower) selectedSets.append("строчные");
    if (params.useUpper) selectedSets.append("заглавные");
    if (params.useDigits) selectedSets.append("цифры");
    if (params.useSymbols) selectedSets.append("символы");

    m_paramsLabel->setText(
        QString("Последние параметры: %1 символов, %2 паролей; наборы: %3")
            .arg(params.length)
            .arg(params.count)
            .arg(selectedSets.isEmpty() ? "не выбраны" : selectedSets.join(", ")));
}

void MainWindow::displayPasswords(const QStringList& passwords) {
    m_passwordsView->setPlainText(
        passwords.isEmpty() ? "Пароли не сгенерированы." : passwords.join('\n'));
}