#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

#include "roundprogress.h"

#include "theme.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    Setting(QWidget *parent = nullptr);
    ~Setting();

    bool loadThemeJson();

    void themeLoad(Theme th);

private:
    Ui::Setting *ui;

    RoundProgress* m_rp;

    QList<Theme> m_themeList;

public Q_SLOTS:
    void slt_themeChanged(int index);
};

#endif // SETTING_H
