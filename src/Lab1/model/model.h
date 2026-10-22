#pragma once

#include <QObject>
#include <QStringList>

inline constexpr int MaxPasswordLength = 64;

struct GenerationParams {
    int length = 12;
    int count = 5;
    bool useLower = true;
    bool useUpper = true;
    bool useDigits = true;
    bool useSymbols = false;
};

class PasswordModel : public QObject {
    Q_OBJECT

public:
    explicit PasswordModel(QObject *parent = nullptr);
    void generate(const GenerationParams& params);

signals:
    void passwordsUpdated(const QStringList& passwords);
};