#include "networksubjectinfo.h"

NetworkSubjectInfo::NetworkSubjectInfo(QUrl url, QObject *parent) : QObject(parent)
{
    // json

    connect(&qnam, SIGNAL(finished(QNetworkReply*)),SLOT(jsonDownload(QNetworkReply*)));
    QNetworkRequest jsonRequest(url);
    //jsonRequest.setHeader(QNetworkRequest::ContentTypeHeader,"application/json"); // ##### Header??
    qnam.get(jsonRequest);
}

void NetworkSubjectInfo::jsonDownload(QNetworkReply *pReply)
{
     jsonDownloadedData = pReply->readAll();
     //emit a signal
     pReply->deleteLater();
     emit jsonDownload();
}

QByteArray NetworkSubjectInfo::getJsonArray() const
{
    return jsonDownloadedData;
}

