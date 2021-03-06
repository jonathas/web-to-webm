#include "ui_mainwindow.h"
#include "utilities.h"
#include "window.h"

#include <QStyleFactory>

Window win;

Window::Window() {
}

void Window::setTheme() {
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette p = qApp->palette();
    p.setColor(QPalette::Window, QColor("#333"));
    p.setColor(QPalette::Button, QColor("#333"));
    p.setColor(QPalette::Highlight, QColor("#b31217"));
    p.setColor(QPalette::ButtonText, QColor("#888"));
    p.setColor(QPalette::WindowText, QColor("#888"));
    p.setColor(QPalette::Dark, QColor("#333"));
    p.setColor(QPalette::Light, QColor("#333"));
    qApp->setPalette(p);
    setStylesheet();
}

void Window::setStylesheet() {
    const char *css =
        "QPushButton:hover{background:#7d1cb4;}"
        "QWebView{background:#333;} QPlainTextEdit{background:#333;}"
        "QLineEdit{background:#888;border:none;height:35px;padding-left:10px;padding-right:10px;color:#222;}"
        "QProgressBar{background:#888; border:none;height:35px;color:#333;}"
        "QProgressBar::chunk{background:#b31217;}"
        "QPlainTextEdit{color:#888;}"
        "QComboBox{height:35px;border:none;background:#888;color:#333;}"
        "QComboBox::drop-down{border:none;background:#222;}"
        "QComboBox::drop-down::pressed{background:#b31217;}"
        "QComboBox QAbstractItemView{padding:15px;background:#888;}"
        "QMenu {background:#333;}"
        "QMenu::item{}"
        "QMenu::item::selected{background:#b31217;}"
        "QPushButton{border:none;background-color:#888;padding:25px;color:#333;}"
        "QPushButton::hover{background:#b31217;}"
        "QMessageBox{background:#222;}"
        "QToolButton{background:#222;border:none;width:35px;height:35px;}"
        "QToolButton:hover{background:#b31217;}"
        "#logBox{background:#333;border: 1px solid #3a3a3a;}"
        "QSpinBox{background:#888;border:none;height:35px;}";

    qApp->setStyleSheet(css);
}

void Window::setPlayerHtml() {
    const char *html =
        "<style>body{background:#222;color:#888;font-family: 'Lucida Console', Monaco, monospace;}"
        "#banner{width:100%;height:100%;text-align:center;font-size:2em;}</style>"
        "<table id='banner'><tr><td>Please, enter video URL<br><br></td></tr></table>";

    win.ui->player->setHtml(html);
}

void Window::setQualityList() {
    win.ui->qualityComboBox->blockSignals(true);
    for (int i=0; i < utils.currentQualityList.size(); i++)
        win.ui->qualityComboBox->addItem(utils.currentQualityList[i][0]);
    win.ui->qualityComboBox->blockSignals(false);
}

void Window::setVideoDetails(QString url) {
    reset();
    openUrlInPlayer(url);
    ui->titleEdit->setText(utils.getVideoTitle(url));
    setQualityList();
    utils.currentFileName = utils.getDefaultFilename();
    setFilename();
    utils.currentVideoUrl = url;
    win.lockAllControls(false);
}

void Window::openUrlInPlayer(QString url) {
    if (url.contains("youtu"))
        win.ui->player->load("https://www.youtube.com/embed/" + utils.currentID);
    else
        win.ui->player->load(url);
}

void Window::reset() {
    win.resetProgress();
    win.ui->filenameEdit->clear();
    win.ui->cutFromEdit->clear();
    win.ui->cutToEdit->clear();
    win.ui->qualityComboBox->blockSignals(true);
    win.ui->qualityComboBox->clear();
    win.ui->qualityComboBox->blockSignals(false);
    win.ui->bitrateValue->clear();
    win.ui->estSize->clear();
}

void Window::resetProgress() {
    win.ui->downloadProgressBar->setValue(0);
    win.ui->conversionProgressBar->setValue(0);
}

void Window::lockAllControls(bool status) {
    win.ui->cutFromEdit->setDisabled(status);
    win.ui->cutToEdit->setDisabled(status);
    win.ui->selectSavePath->setDisabled(status);
    win.ui->startConversion->setDisabled(status);
    win.ui->bitrateValue->setDisabled(status);
}

void Window::setFilename() {
    win.ui->filenameEdit->setText(utils.getCurrentFilename());
}

void Window::updateConversionButton() {
    QIcon icon;
    if (ui->startConversion->isChecked()) {
        icon = QIcon(":/icons/cancel.png");
    } else {
        icon = QIcon(":/icons/convert.png");
    }
    ui->startConversion->setIcon(icon);
}

void Window::toggleConversionButton() {
    ui->startConversion->toggle();
    updateConversionButton();
}
