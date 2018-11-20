#ifndef NETWORKSUBJECTINFO_H
#define NETWORKSUBJECTINFO_H

#include <QObject>
#include <QUrl>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


class NetworkCourseInfo : public QObject
{
    Q_OBJECT
public:
    explicit NetworkCourseInfo(QUrl Url, QObject *parent = nullptr);
    //virtual ~NetworkSubjectInfo();

    QByteArray getJsonArray() const;


signals:
    void jsonDownload();



private slots:
    void jsonDownload(QNetworkReply *pReply);
private:
    QNetworkAccessManager qnam;
    QByteArray jsonDownloadedData;


};

#endif // NETWORKSUBJECTINFO_H
