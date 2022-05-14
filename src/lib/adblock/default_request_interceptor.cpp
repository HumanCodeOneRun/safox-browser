#include "default_request_interceptor.h"

DefaultRequestInterceptor::DefaultRequestInterceptor(QObject *parent) : QWebEngineUrlRequestInterceptor(parent) {

}

void DefaultRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info) {

}