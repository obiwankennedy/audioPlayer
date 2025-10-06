#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QFile>
#include <QSaveFile>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <stdlib.h>
#include "sizedfilesystemmodel.h"

bool dryRun = false;

namespace constants{
constexpr auto playListFile{"/home/renaud/documents/playlist_official.apl"};
constexpr auto music_root{"/media/renaud/musique"};
}

//find . -type d -empty -delete
//ll | wc -l
//1307 dirs



bool makeSurePathExist(const QDir& dir)
{
    qDebug() << "makeSurePathExist" << dir;
    if(dryRun)
        return true;
    if(!dir.exists())
        dir.mkpath(dir.path());

    return dir.exists();
}

bool moveFile(const QString& source, const QString& destination)
{
    qDebug() << "moveFile" << source << destination;
    if(dryRun)
        return true;
    QFile src(source);
    QFileInfo srcInfo(source);
    QFileInfo dest(destination);

    if(dest.isDir())
        dest.setFile(QString("%1/%2").arg(destination, srcInfo.fileName()));

    bool res= false;
    if(makeSurePathExist(dest.dir()))
    {
        res= src.rename(dest.absoluteFilePath());
    }
    return res;
}

bool moveContent(const QString& source, const QString& destination)
{
    qDebug() << "moveConten" << source << destination;
    if(dryRun)
        return true;
    QDir directory(source);
    QFileInfoList files = directory.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for(const QFileInfo &info: std::as_const(files))
    {
        if(info.isFile())
        {
            auto path=  info.absoluteFilePath();
            auto dest = path;
            dest = dest.replace(source, destination);
            qDebug() << "move " << path << dest;
            moveFile(path, dest);
        }
        else if(info.isDir())
        {
            auto name = info.baseName();
            qDebug() << "move Dir:" << info.absoluteFilePath() << destination+"/"+name;
            moveContent(info.absoluteFilePath(), destination+"/"+name);
        }
    }
    return true;
}


bool replacePath(const QString& source, const QString& destination, bool isDir = true)
{
    qDebug() << "replace "<< (isDir ? source+"/": source) << (isDir ? destination+"/":destination);
    if(dryRun)
        return true;
    QFile file(constants::playListFile);
    if(!file.open(QIODevice::ReadOnly))
        return false;

    auto data = QString(file.readAll());


    data.replace(isDir ? source+"/": source, isDir ? destination+"/":destination);

    QSaveFile save(constants::playListFile);

    if(!save.open(QIODevice::WriteOnly))
        return false;

    save.write(data.toUtf8());
    if(save.commit())
        return true;
    else
        return false;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    //, m_model(new SizedFileSystemModel)
    , m_model(new QFileSystemModel)
{
    m_ui->setupUi(this);
    m_model->setRootPath("/media/renaud/musique");
    m_ui->m_fsView->setModel(m_model.get());
    connect(m_ui->m_fsView, &QTreeView::customContextMenuRequested, this, &MainWindow::contextMenu);
    m_ui->m_fsView->setRootIndex(m_model->index("/media/renaud/musique"));
    m_ui->m_fsView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_ui->m_fsView->setColumnWidth(0, 400);
    m_ui->m_fsView->setSelectionMode(QAbstractItemView::ContiguousSelection);

    m_cut.reset(new QAction(tr("Cut")));
    connect(m_cut.get(), &QAction::triggered, this, &MainWindow::cut);
    m_cut->setEnabled(false);

    m_selectForMerge.reset(new QAction(tr("Select For Merge")));
    connect(m_selectForMerge.get(), &QAction::triggered, this, &MainWindow::selectForMerge);
    m_selectForMerge->setEnabled(false);

    m_paste.reset(new QAction(tr("Paste")));
    connect(m_paste.get(), &QAction::triggered, this, &MainWindow::paste);
    m_paste->setEnabled(false);

    m_rename.reset(new QAction(tr("Rename")));
    connect(m_rename.get(), &QAction::triggered, this, &MainWindow::rename);
    m_rename->setEnabled(false);

    m_subDir.reset(new QAction(tr("mkdir")));
    connect(m_subDir.get(), &QAction::triggered, this, &MainWindow::createSubDir);
    m_subDir->setEnabled(false);

    m_check.reset(new QAction(tr("Check Integrity")));
    connect(m_check.get(), &QAction::triggered, this, &MainWindow::checkIntegrity);
    m_check->setEnabled(true);

    m_listUnlisted.reset(new QAction(tr("Show Unlisted Files")));
    connect(m_listUnlisted.get(), &QAction::triggered, this, &MainWindow::unListedFile);
    m_listUnlisted->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::contextMenu(const QPoint &pos)
{
    QMenu menu;

    menu.addAction(m_cut.get());
    menu.addAction(m_selectForMerge.get());
    menu.addAction(m_paste.get());
    menu.addAction(m_rename.get());
    menu.addAction(m_subDir.get());
    menu.addAction(m_check.get());
    menu.addAction(m_listUnlisted.get());

    auto index = m_ui->m_fsView->indexAt(m_cut->data().toPoint());

    m_cut->setEnabled(index.isValid() && !m_model->isDir(index));
    m_cut->setData(pos);

    m_selectForMerge->setEnabled(index.isValid() && m_model->isDir(index));
    m_selectForMerge->setData(pos);

    m_rename->setEnabled(index.isValid() && m_model->isDir(index));
    m_rename->setData(pos);

    m_paste->setEnabled(!m_cutPath.isEmpty() || !m_paths.empty());
    m_paste->setData(pos);

    m_subDir->setEnabled(index.isValid() && m_model->isDir(index));
    m_subDir->setData(pos);


    menu.exec(mapToGlobal(pos));
}

void MainWindow::cut()
{
    m_paths.empty();
    auto selectModel = m_ui->m_fsView->selectionModel();
    auto indexes = selectModel->selectedIndexes();
    for(auto idx : std::as_const(indexes))
    {
        m_paths << m_model->filePath(idx);
    }

}

void MainWindow::paste()
{
    auto destination = m_ui->m_fsView->indexAt(m_paste->data().toPoint());
    auto destPath = m_model->filePath(destination);
    if(!m_cutPath.isEmpty())
    {
        if(moveContent(m_cutPath, destPath))
        {
            replacePath(m_cutPath, destPath);
        }
    }
    else if(!m_paths.empty())
    {
        for(auto const& path : std::as_const(m_paths))
        {
            QFileInfo info(path);
            auto fileName = info.fileName();
            moveFile(path, destPath+'/'+fileName);
            replacePath(path, destPath+'/'+fileName, false);
        }
    }

    m_cutPath = "";
    m_paths.clear();
}

void MainWindow::selectForMerge()
{
    auto index = m_ui->m_fsView->indexAt(m_cut->data().toPoint());
    m_cutPath = m_model->filePath(index);
}

void MainWindow::rename()
{
    auto index = m_ui->m_fsView->indexAt(m_rename->data().toPoint());
    auto sourcePath = m_model->filePath(index);
    QFileInfo info(sourcePath);

    auto name = info.fileName();

    auto newName = QInputDialog::getText(this, tr("New name"), tr("New name"),QLineEdit::Normal,name);

    if(newName.isEmpty())
        return;

    auto path = info.absolutePath();


    if(!dryRun)
    {
        QFile::rename(sourcePath, path+'/'+newName);
    }
    replacePath(sourcePath, path+'/'+newName);
}

void MainWindow::createSubDir()
{
    auto index = m_ui->m_fsView->indexAt(m_subDir->data().toPoint());
    auto sourcePath =m_model->filePath(index);
    QFileInfo info(sourcePath);

    auto path = info.absolutePath();
    auto newName = QInputDialog::getText(this, tr("New name"), path,QLineEdit::Normal);
    if(newName.isEmpty())
        return;

    auto dir = info.dir();
    dir.cd(newName);
    makeSurePathExist(dir);
}

void MainWindow::checkIntegrity()
{
    QFile file(constants::playListFile);

    if(!file.open(QIODevice::ReadOnly))
        return;

    auto doc = QJsonDocument::fromJson(file.readAll());

    auto songs = doc.object().value("songs").toArray();

    qDebug() << "Not Existing Files";
    qDebug() << "##################";
    for(auto const& arrayItem : std::as_const(songs))
    {
        auto song = arrayItem.toObject();
        QFileInfo info(song["path"].toString());

        if(!info.exists())
            qDebug() << info.absoluteFilePath();
    }

    qDebug() << "##################";
}

void recursiveListFile(QSet<QString>& files, const QString& path)
{
    QDir dir(path);
    auto infos = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for(auto const &entry: std::as_const(infos))
    {
        if(entry.isDir())
        {
            recursiveListFile(files,entry.absoluteFilePath());
        }
        else
        {
            files.insert(entry.absoluteFilePath());
        }
    }
}

void MainWindow::unListedFile()
{
    // files
    QSet<QString> files;
    recursiveListFile(files, constants::music_root);

    qDebug() << "files count:" << files.count();

    // songs
    QFile file(constants::playListFile);
    if(!file.open(QIODevice::ReadOnly))
        return;
    auto doc = QJsonDocument::fromJson(file.readAll());
    auto songList = doc.object().value("songs").toArray();

    //remove songs from the file list
    for(auto const& arrayItem : std::as_const(songList))
    {
        auto song = arrayItem.toObject();
        files.remove(song["path"].toString());
    }

    //show the list:
    qDebug() << "@@@@@@@@@@@@@@@@";
    for(auto const& file : std::as_const(files))
    {
        qDebug() << "," << file;
    }
    qDebug() << "@@@@@@@@@@@@@@@@";
}
