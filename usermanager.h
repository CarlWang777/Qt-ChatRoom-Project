#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>

class UserManager
{
public:
    UserManager();

    // 验证用户凭据 (替代旧的 checkCredentials)
    bool validateUser(const QString &username, const QString &password);

    // 添加新用户 (替代旧的 saveUser)
    bool addUser(const QString &username, const QString &password);

    // 检查用户是否存在 (替代旧的 userExists)
    bool userExists(const QString &username);

private:
    // 获取数据文件路径 (这是内部实现，不对外暴露)
    QString dataFilePath() const;

    // 对密码进行哈希计算
    QByteArray hashPassword(const QString &password) const;
};

#endif // USERMANAGER_H
