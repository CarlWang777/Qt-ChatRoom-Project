#include "usermanager.h"
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QCryptographicHash>

UserManager::UserManager()
{
}

QString UserManager::dataFilePath() const
{
    QDir dir(QCoreApplication::applicationDirPath());
    return dir.filePath("data.txt");
}

QByteArray UserManager::hashPassword(const QString &password) const
{
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
}

bool UserManager::addUser(const QString &username, const QString &password)
{
    QFile file(dataFilePath());
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        return false;
    }

    const QString passwordHash = QString(hashPassword(password).toHex());

    const QString line = QString("%1 %2;\n").arg(username, passwordHash);
    const qint64 written = file.write(line.toUtf8());
    file.close();
    return written > 0;
}

bool UserManager::validateUser(const QString &username, const QString &password)
{
    QFile file(dataFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    const QString inputPasswordHash = QString(hashPassword(password).toHex());

    static const QRegularExpression re(R"(^(\S+)\s+(.*);$)");
    while (!file.atEnd())
    {
        const QString line = QString::fromUtf8(file.readLine()).trimmed();
        if (line.isEmpty()) continue;

        const auto m = re.match(line);
        if (!m.hasMatch()) continue;

        const QString storedUser = m.captured(1);
        const QString storedHash = m.captured(2);

        if (storedUser == username) {
            file.close();
            return storedHash == inputPasswordHash;
        }
    }
    file.close();
    return false;
}

bool UserManager::userExists(const QString &username)
{
    QFile file(dataFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    static const QRegularExpression re(R"(^(\S+)\s+(.*);$)");
    while (!file.atEnd())
    {
        const QString line = QString::fromUtf8(file.readLine()).trimmed();
        if (line.isEmpty()) continue;

        const auto m = re.match(line);
        if (!m.hasMatch()) continue;

        const QString storedUser = m.captured(1);
        if (storedUser == username)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
