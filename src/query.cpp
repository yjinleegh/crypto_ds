#include "query.h"
#include <string>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "util/time_conv.h"

#define HOUR "3600"
#define DAY "86400"

using namespace std;
using namespace rapidjson;

    // //c.get_account();
    // //c.get_single_market("BTC/USD");
    // Document doc = c.get_single_orderbook("BTC/USD", "20");

    // Parser p;
    // p.parse_orderbook(&doc);

    // //c.get_trades("BTC/USD", "20");
    // Document doc2 = c.get_hist_recent("BTC/USD", "60", "200");
    // p.parse_historical(&doc2);

// Get historical data for the last one year in the interval of one day
vector<hist_p> Query::get_year_hist(string market){

    Document doc = this->client->get_hist_recent(market, DAY, "365");
    Parser psr;

    vector<hist_p> v;
    psr.ser_historical(&doc, &v);

    return v;
}

// Get historical data from the start time specified in the interval of one day
vector<hist_p> Query::get_hist_from(string market, string start_time){
    string t = date_to_epoch(start_time);
    
    Document doc = this->client->get_hist_specified(market, DAY, "", t, "");
    Parser psr;

    vector<hist_p> v;
    psr.ser_historical(&doc, &v);

    this->db->insert_hist("new", &v);

    return v;
}

// Get historical data for a custom range of time with custom interval and limit.
// Can specify start_time, end_time and limit as null ("").
vector<hist_p> Query::get_hist_custom(string market, string start_time, string end_time, string resolution, string limit){

    Document doc = this->client->get_hist_specified(market, resolution, limit, start_time, end_time);
    Parser psr;

    vector<hist_p> v;
    psr.ser_historical(&doc, &v);

    return v;
}

// TODO: Create methods for writing to file instead of writing to db and stdout