#include "mainimagedownloader.h"
#include <QNetworkReply>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QThread>

MainImageDownloader::MainImageDownloader(QObject *parent) : QObject(parent) {
    m_imageCounter = 1; // Инициализация счетчика для уникальных имен файлов
}

void MainImageDownloader::downloadImage(const QString &url, const QString &filename) {
    QThread* thread = new QThread;
    ImageDownloader* imageDownloader = new ImageDownloader(url, m_imageCounter);
    imageDownloader->moveToThread(thread);

    connect(thread, &QThread::started, imageDownloader, &ImageDownloader::download);
    connect(imageDownloader, &ImageDownloader::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(imageDownloader, &ImageDownloader::imageDownloaded, this, &MainImageDownloader::handleImageDownloaded);
    connect(imageDownloader, &ImageDownloader::downloadProgress, [this, imageDownloader](qint64 bytesReceived, qint64 bytesTotal) {
        emit downloadProgress(imageDownloader->imageCounter(), bytesReceived, bytesTotal); // Исправлено
    });

    thread->start();
    m_imageCounter++;
}

void MainImageDownloader::handleImageDownloaded(const QString &filePath) {
    qDebug() << "Image saved as: " << filePath;
}

ImageDownloader::ImageDownloader(const QString &url, int imageCounter) : m_url(url), m_imageCounter(imageCounter) {
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &ImageDownloader::onDownloadFinished);
}

void ImageDownloader::download() {
    QUrl imageUrl(m_url);
    QNetworkReply *reply = m_networkAccessManager.get(QNetworkRequest(imageUrl));
    connect(reply, &QNetworkReply::downloadProgress, this, &ImageDownloader::downloadProgress);
}



void ImageDownloader::onDownloadFinished(QNetworkReply *reply) {
    if(reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();

        QString directoryPath = "/Users/philippogorodnikov/poehali_v2/images/";
        QDir directory(directoryPath);
        if (!directory.exists()) {
            directory.mkpath(".");
        }

        QString uniqueFileName = "image_" + QString::number(m_imageCounter) + ".jpg";
        QString filePath = directoryPath + uniqueFileName;
            emit downloadProgress(reply->bytesAvailable(), reply->header(QNetworkRequest::ContentLengthHeader).toLongLong());
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(imageData);
            file.close();
            emit imageDownloaded(filePath);
        } else {
            qDebug() << "Error saving image";
        }
    } else {
        qDebug() << "Error downloading image: " << reply->errorString();
    }
    reply->deleteLater();
}
