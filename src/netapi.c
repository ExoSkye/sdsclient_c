#include <curl/curl.h>
#include <malloc.h>
#include <string.h>
#include "netapi.h"
#include "config.h"

CURL* curl_ctx;

#define ENOUGH ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t
writeMemoryCallbackCurl(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

bool netInit() {
    curl_global_init(0);
    curl_ctx = curl_easy_init();
    char* user_pwd_combo = (char*)malloc(strlen(getUsername())+1+strlen(getPassword())+1);
    user_pwd_combo[strlen(getUsername())+1+strlen(getPassword())] = '\0';
    memcpy(user_pwd_combo,getUsername(),strlen(getUsername()));
    user_pwd_combo[strlen(getUsername())] = ':';
    memcpy(&user_pwd_combo[strlen(getPassword())+1],getPassword(),strlen(getPassword()));
    curl_easy_setopt(curl_ctx, CURLOPT_USERPWD, user_pwd_combo);
    curl_easy_setopt(curl_ctx, CURLOPT_HTTPAUTH, (long)CURLAUTH_DIGEST);
    free(user_pwd_combo);
    return true;
}

void netDelete() {
    curl_easy_cleanup(curl_ctx);
    curl_global_cleanup();
}

struct MemoryStruct getReq(const char* path) {
    CURLcode result;
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;
    int length = snprintf(NULL, 0,"%d",getPort());
    char* port = (char*)malloc(length+1);
    sprintf(port, "%d", getPort());
    char* url = (char*)malloc(strlen(getScheme())+strlen("://")+strlen(getIp())+strlen(":")+strlen(port)+strlen(path)+1);
    memcpy(url,getScheme(),strlen(getScheme()));
    memcpy(&url[strlen(getScheme())],"://",strlen("://"));
    memcpy(&url[strlen(getScheme())+strlen("://")],getIp(),strlen(getIp()));
    memcpy(&url[strlen(getScheme())+strlen("://")+strlen(getIp())],":",strlen(":"));
    memcpy(&url[strlen(getScheme())+strlen("://")+strlen(getIp())+strlen(":")],port,strlen(port));
    memcpy(&url[strlen(getScheme())+strlen("://")+strlen(getIp())+strlen(":")+strlen(port)],path,strlen(path));
    url[strlen(getScheme())+strlen("://")+strlen(getIp())+strlen(":")+strlen(port)+strlen(path)] = '\0';
    curl_easy_setopt(curl_ctx, CURLOPT_URL,url);
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEFUNCTION, writeMemoryCallbackCurl);
    curl_easy_setopt(curl_ctx, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_ctx, CURLOPT_USERAGENT, "libcurl-sdsclient/1.0");
    result = curl_easy_perform(curl_ctx);
    if (result != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
    }
    else {
        free(url);
        return chunk;
    }
    free(url);
    free(chunk.memory);
    return chunk;
}

const char* netGetConfig() {
    struct MemoryStruct chunk = getReq("/digest/getConfig");
    printf("%s",chunk.memory);
}

const char* netGetReload() {

}