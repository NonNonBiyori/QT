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
    void slot_vedio_player();        // QT������Ƶ
    void slot_opencv_vedio_player(); // opencv������Ƶ
    void slot_opencv_jpeg_player();  // opencv��ͼƬ
    void slot_open_file_path();      // ѡ���ļ���
    void slot_double_click_file(QTreeWidgetItem* item, int column); // ѡ���ļ�
    void slot_click_pre_image();     // ��һ��
    void slot_click_pos_image();     // ��һ��
    void slot_click_large_image();   // �Ŵ�
    void slot_click_small_image();   // ��С
    void slot_click_delete();        // ɾ��
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject* target, QEvent* event);

private:
    void init();
    void setFiles(QString dirStr, QTreeWidgetItem* root=nullptr);
    void opencv_show_image(std::string imagePath);
    void opencv_show_imageByOpencv(std::string imagePath);
    void opencv_show_imageByQT(std::string imagePath);

private:
    Ui::MainWindow *ui;
    std::map<std::string, std::vector<std::string> > m_fileNameMap; // <�ļ��У��ļ����µ��ļ�

};

#endif // MAINWINDOW_H
