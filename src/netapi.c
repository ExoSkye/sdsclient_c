#include <curl/curl.h>
#include "netapi.h"

CURL* curl_ctx;

void net_init() {
    curl_ctx = curl_easy_init();
    curl_easy_setopt(curl_ctx, CURLOPT_USERPWD, "user:pwd");
    curl_easy_setopt(curl_ctx, CURLOPT_HTTPAUTH, (long)CURLAUTH_DIGEST);
}