#include "chatdialog.h"
#include "registerdialog.h"
#include "ui_chatdialog.h"
#include "usermanager.h"

#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QStandardPaths>

chatDialog::chatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatDialog)
{
    ui->setupUi(this);
    // 启动时隐藏警告
    ui->lbWarning->setVisible(false);

    // 回车提交
    connect(ui->edtUserName, &QLineEdit::returnPressed, ui->pbLogin, &QPushButton::click);
    connect(ui->edtUserPass, &QLineEdit::returnPressed, ui->pbLogin, &QPushButton::click);

}

chatDialog::~chatDialog()
{
    delete ui;
}

void chatDialog::on_pbLogin_clicked()
{
    const QString user = ui->edtUserName->text().trimmed();
    const QString pass = ui->edtUserPass->text();

    if (user.isEmpty() || pass.isEmpty())
    {
        return;
    }

    UserManager userManager;

    if (userManager.validateUser(user, pass))
    {
        ui->lbWarning->setVisible(false);
        accept();
    }
    else
    {
        ui->lbWarning->setText("用户名或密码不正确！");
        ui->lbWarning->setVisible(true);
        ui->edtUserPass->selectAll();
        ui->edtUserPass->setFocus();
    }
}

void chatDialog::on_pbRegister_clicked()
{
    registerdialog reg(this);
    if (reg.exec() == QDialog::Accepted)
    {

        ui->edtUserName->setText(reg.registeredUser());
        ui->edtUserPass->clear();
        ui->edtUserPass->setFocus();
    }
}

