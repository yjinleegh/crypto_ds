#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <fstream>
#include <curl/curl.h>
#include "rapidjson/document.h"

class Client{
    public:
        Client(std::string endpoint){
            this->endpoint = endpoint;

            std::ifstream file;
            file.open("ftx_key.txt");
            file >> this->key >> this->secret;
            file.close();
            //Add confirmation output
        };

        rapidjson::Document get_account();
        rapidjson::Document get_single_market(std::string market);
        rapidjson::Document get_single_orderbook(std::string market, std::string depth);
        rapidjson::Document get_trades(std::string market, std::string limit);
        rapidjson::Document get_hist_specified(std::string market, std::string resolution, std::string limit, std::string start_time, std::string end_time);
        rapidjson::Document get_hist_recent(std::string market, std::string resolution, std::string limit);

    private:
        std::string endpoint;
        std::string key;
        std::string secret;
        std::string endpoint_append(std::string path);
        struct curl_slist* set_header(struct curl_slist * slist, std::string path);
        static size_t write_response(void * data, size_t size, size_t nmemb, void * userp);
        rapidjson::Document send_request(std::string url, struct curl_slist* slist);
};

// struct typedef to declare memory struct for storing reponse data
typedef struct _mem_struct
{

  char *memory;
  size_t size;

} mem_struct;


#endif /* CLIENT_H */