#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class registerdialog;
}

class registerdialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerdialog(QWidget *parent = nullptr);
    ~registerdialog();
    QString registeredUser() const
    {
        return m_registeredUser;
    }

private slots:
    void on_pbRegister_clicked();
    void on_pbCancel_clicked();

private:
    Ui::registerdialog *ui;
    QString m_registeredUser;

};

#endif // REGISTERDIALOG_H
