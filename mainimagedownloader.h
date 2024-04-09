#ifndef MAINIMAGEDOWNLOADER_H
#define MAINIMAGEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>

class ImageDownloader : public QObject {
    Q_OBJECT
public:
    explicit ImageDownloader(const QString &url, int imageCounter);
    int imageCounter() const { return m_imageCounter; } // Добавлено

public slots:
    void download();

signals:
    void finished();
    void imageDownloaded(const QString &filePath);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void onDownloadFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkAccessManager;
    QString m_url;
    int m_imageCounter;
};

class MainImageDownloader : public QObject {
    Q_OBJECT
public:
    explicit MainImageDownloader(QObject *parent = nullptr);
public slots:
    void downloadImage(const QString &url, const QString &filename);
    void handleImageDownloaded(const QString &filePath);
signals:
    void downloadProgress(int imageCounter, qint64 bytesReceived, qint64 bytesTotal);
private:
    int m_imageCounter;
};


#endif // MAINIMAGEDOWNLOADER_H
