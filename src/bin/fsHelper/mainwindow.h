#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QAction>
#include <memory>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void contextMenu(const QPoint& pos);

    void cut();
    void paste();
    void selectForMerge();
    void rename();
    void createSubDir();
    void checkIntegrity();
    void unListedFile();

private:
    Ui::MainWindow* m_ui;
    std::unique_ptr<QFileSystemModel> m_model;


    std::unique_ptr<QAction> m_rename;
    std::unique_ptr<QAction> m_cut;
    std::unique_ptr<QAction> m_selectForMerge;
    std::unique_ptr<QAction> m_paste;
    std::unique_ptr<QAction> m_subDir;
    std::unique_ptr<QAction> m_check;
    std::unique_ptr<QAction> m_listUnlisted;
    QString m_cutPath;
    QSet<QString> m_paths;
};

#endif
