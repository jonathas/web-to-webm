#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"

#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    utils.ui = ui;
    utils.setTheme();
    utils.setCommons();
    utils.currentDownloadProcess = new QProcess;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_urlEdit_returnPressed() {
    utils.setVideoDetails(ui->urlEdit->text());
}

void MainWindow::on_selectSavePath_clicked() {
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Select location for converted film"), QDir::currentPath(), tr("Webm (*.webm)") );

    if (!filename.isEmpty())
        ui->filenameEdit->setText(filename);
}

void MainWindow::on_stopConversion_clicked() {
    if (utils.currentDownloadProcess->atEnd())
        utils.currentDownloadProcess->close();
}

void MainWindow::on_startConversion_clicked() {
    if (!utils.startProcedure())
        return;

    if (utils.currentDownloadProcess->atEnd())
        utils.currentDownloadProcess->close();

    downloadProcess(utils.ytBinaryName() + " -f " + utils.ytGetQuality() + " " + utils.currentVideoUrl);
}

void MainWindow::downloadProcess(QString bin) {
    utils.currentDownloadProcess = new QProcess;
    utils.currentDownloadProcess->start(bin);

    connect(utils.currentDownloadProcess, SIGNAL(readyReadStandardOutput()), &utils, SLOT(downloadProgress()));
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "ytwebm about", "This software is open source (MIT licensed). It was build with QT5, youtube-dl and ffmpeg. For more informations see https://github.com/solusipse/ytwebm.");
}
