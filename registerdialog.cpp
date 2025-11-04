#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "usermanager.h"

#include <QDir>
#include <QFile>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>

registerdialog::registerdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerdialog)
{
    ui->setupUi(this);

    ui->lbRegWarning->setVisible(false);
    ui->edtRegPass->setEchoMode(QLineEdit::Password);
    ui->edtRegPassConfirm->setEchoMode(QLineEdit::Password);
    ui->edtRegPass->setMaxLength(32);
    ui->edtRegPassConfirm->setMaxLength(32);
    ui->edtRegPass->setPlaceholderText("至少6位");
    ui->edtRegPassConfirm->setPlaceholderText("再次输入密码");

    connect(ui->pbRegister, &QPushButton::clicked, this, &registerdialog::on_pbRegister_clicked);
}

registerdialog::~registerdialog()
{
    delete ui;
}

void registerdialog::on_pbRegister_clicked()
{
    const QString user = ui->edtRegUserName->text().trimmed();
    const QString pass = ui->edtRegPass->text();
    const QString confirm = ui->edtRegPassConfirm->text();

    if (user.isEmpty() || pass.isEmpty() || pass.size() < 6 || pass != confirm)
    {

        if (pass != confirm)
        {
            ui->lbRegWarning->setText("两次输入的密码不一致！");
            ui->lbRegWarning->setVisible(true);
            return;
        }
        return;
    }

    UserManager userManager;

    if (userManager.userExists(user))
    {
        ui->lbRegWarning->setText("该用户名已存在！");
        ui->lbRegWarning->setVisible(true);
        ui->edtRegUserName->setFocus();
        ui->edtRegUserName->selectAll();
        return;
    }

    if (!userManager.addUser(user, pass))
    {
        QMessageBox::critical(this, "错误", "保存用户数据失败！");
        return;
    }

    m_registeredUser = user;
    ui->lbRegWarning->setVisible(false);
    accept();
}


void registerdialog::on_pbCancel_clicked()
{
    reject();
}


