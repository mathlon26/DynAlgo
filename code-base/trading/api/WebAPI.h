#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QList>
#include <functional>
#include <QHash>


class WebAPI : public QObject {
    Q_OBJECT

protected:
    using Callback = std::function<void(QNetworkReply*)>;

    explicit WebAPI(QObject *parent = nullptr)
        : QObject{parent}, m_manager(new QNetworkAccessManager(this)) {
        connect(m_manager, &QNetworkAccessManager::finished, this, &WebAPI::onFinished);
    }

    void get(const QString &endpoint, std::initializer_list<QPair<QString, QString>> headers = {}, Callback callback = nullptr) {
        sendRequest(QNetworkAccessManager::GetOperation, endpoint, QJsonObject(), headers, callback);
    }

    void post(const QString &endpoint, const QJsonObject &body, std::initializer_list<QPair<QString, QString>> headers = {}, Callback callback = nullptr) {
        sendRequest(QNetworkAccessManager::PostOperation, endpoint, body, headers, callback);
    }

    void put(const QString &endpoint, const QJsonObject &body, std::initializer_list<QPair<QString, QString>> headers = {}, Callback callback = nullptr) {
        sendRequest(QNetworkAccessManager::PutOperation, endpoint, body, headers, callback);
    }

    void deleteRequest(const QString &endpoint, std::initializer_list<QPair<QString, QString>> headers = {}, Callback callback = nullptr) {
        sendRequest(QNetworkAccessManager::DeleteOperation, endpoint, QJsonObject(), headers, callback);
    }

private:
    void sendRequest(QNetworkAccessManager::Operation operation,
                     const QString &endpoint,
                     const QJsonObject &body,
                     std::initializer_list<QPair<QString, QString>> headers,
                     Callback callback) {

        QNetworkRequest request(endpoint);
        QSet<QString> uniqueKeys;
        for (const auto &header : headers) {
            if (!header.first.isEmpty() && !uniqueKeys.contains(header.first)) {
                request.setRawHeader(header.first.toUtf8(), header.second.toUtf8());
                uniqueKeys.insert(header.first);
            }
        }

        QNetworkReply *reply = nullptr;

        if (operation == QNetworkAccessManager::PostOperation || operation == QNetworkAccessManager::PutOperation) {
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            QJsonDocument doc(body);
            QByteArray data = doc.toJson();
            reply = m_manager->sendCustomRequest(request, operationName(operation), data);
        } else {
            reply = m_manager->sendCustomRequest(request, operationName(operation));
        }

        if (callback && reply) {
            m_callbacks.insert(reply, callback);
        }
    }

    QByteArray operationName(QNetworkAccessManager::Operation operation) const {
        switch (operation) {
        case QNetworkAccessManager::PostOperation: return "POST";
        case QNetworkAccessManager::GetOperation: return "GET";
        case QNetworkAccessManager::PutOperation: return "PUT";
        case QNetworkAccessManager::DeleteOperation: return "DELETE";
        default: return "";
        }
    }

private slots:
    void onFinished(QNetworkReply *reply) {
        if (m_callbacks.contains(reply)) {
            m_callbacks[reply](reply);
            m_callbacks.remove(reply);
        }
        reply->deleteLater();
    }

private:
    QNetworkAccessManager *m_manager;
    QHash<QNetworkReply*, Callback> m_callbacks;
};

#endif // WEBAPI_H
