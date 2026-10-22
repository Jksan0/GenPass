#include "model.h"

#include <QRandomGenerator>

PasswordModel::PasswordModel(QObject *parent)
    : QObject(parent) {}

void PasswordModel::generate(const GenerationParams& params) {
    const QString lower = "abcdefghijklmnopqrstuvwxyz";
    const QString upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString digits = "0123456789";
    const QString symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    QStringList selectedSets;
    if (params.useLower) selectedSets.append(lower);
    if (params.useUpper) selectedSets.append(upper);
    if (params.useDigits) selectedSets.append(digits);
    if (params.useSymbols) selectedSets.append(symbols);

    QString availableCharacters;
    for (const QString& characterSet : selectedSets) {
        availableCharacters += characterSet;
    }

    QStringList passwords;
    if (availableCharacters.isEmpty()
        || params.length > MaxPasswordLength
        || params.length < selectedSets.size()
        || params.count <= 0) {
        emit passwordsUpdated(passwords);
        return;
    }

    QRandomGenerator *random = QRandomGenerator::system();
    for (int passwordIndex = 0; passwordIndex < params.count; ++passwordIndex) {
        QString password;
        for (const QString& characterSet : selectedSets) {
            const int characterIndex = random->bounded(characterSet.size());
            password.append(characterSet.at(characterIndex));
        }

        while (password.size() < params.length) {
            const int characterIndex = random->bounded(availableCharacters.size());
            password.append(availableCharacters.at(characterIndex));
        }

        for (int index = password.size() - 1; index > 0; --index) {
            const int otherIndex = random->bounded(index + 1);
            const QChar character = password.at(index);
            password[index] = password.at(otherIndex);
            password[otherIndex] = character;
        }
        passwords.append(password);
    }

    emit passwordsUpdated(passwords);
}