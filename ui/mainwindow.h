/*
 * Copyright [2019]
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma execution_character_set("utf-8") 

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <string>
#include <vector>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_vedio_player();
    void slot_opencv_vedio_player();
    void slot_opencv_jpeg_player();
    void slot_open_file_path();
    void slot_click_file(QTreeWidgetItem* item, int column);

private:
    void init();
    void setFiles(QString dirStr, QTreeWidgetItem* root=nullptr);
    void opencv_show_image(std::string imagePath);

private:
    Ui::MainWindow *ui;
    std::map<std::string, std::vector<std::string> > m_fileNameMap; // <文件夹，文件夹下的文件

};

#endif // MAINWINDOW_H
