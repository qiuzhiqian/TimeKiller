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

    //void addTask();

private:
    Ui::Setting *ui;

    RoundProgress* m_rp;

    ThemeList* m_themeList;
    TaskList* m_taskList;

    void init();

public Q_SLOTS:
    void slt_themeChanged(int index);
    void slt_addTask();
    void slt_removeTask(int row,int column);
};

#endif // SETTING_H
