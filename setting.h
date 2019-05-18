#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

#include "roundprogress.h"

#include "theme.h"
#include "task.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    Setting(ThemeList* tl,TaskList* tkl, QWidget *parent = nullptr);
    ~Setting();

    void themeLoad(Theme th);

private:
    Ui::Setting *ui;

    RoundProgress* m_rp;

    ThemeList* m_themeList;
    TaskList* m_taskList;

    void init();

public Q_SLOTS:
    void slt_themeChanged(int index);
};

#endif // SETTING_H
