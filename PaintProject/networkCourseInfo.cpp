#include "networkCourseInfo.h"

NetworkCourseInfo::NetworkCourseInfo(QUrl url, QObject *parent) : QObject(parent)
{
    // json

    connect(&qnam, SIGNAL(finished(QNetworkReply*)),SLOT(jsonDownload(QNetworkReply*)));
    QNetworkRequest jsonRequest(url);
    //jsonRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json"); // ##### Header??
    qnam.get(jsonRequest);
}

void NetworkCourseInfo::jsonDownload(QNetworkReply *pReply)
{
     jsonDownloadedData = pReply->readAll();
     //emit a signal
     pReply->deleteLater();
     emit jsonDownload();
}

QByteArray NetworkCourseInfo::getJsonArray() const
{
    return jsonDownloadedData;
}

