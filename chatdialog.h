#ifndef CHATDIALOG_H
#define CHATDIALOG_H


#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class chatDialog; }
QT_END_NAMESPACE

class chatDialog : public QDialog
{
    Q_OBJECT

public:
    chatDialog(QWidget *parent = nullptr);
    ~chatDialog();
private slots:
    void on_pbLogin_clicked();
    void on_pbRegister_clicked();

private:
    Ui::chatDialog *ui;
};
#endif // CHATDIALOG_H
