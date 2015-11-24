// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "RPCService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
#include <cstdio>
#include <curl/curl.h>
#include "PageCache.h"

using boost::shared_ptr;

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::server;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace ::RPC;

size_t writeResponse(void * buf, size_t size, size_t nmemb, void* up)
{   
  WebPage *webpage_ptr = (WebPage *)up;
  while(webpage_ptr->len + (size * nmemb) >= webpage_ptr->size) {
    webpage_ptr->data = (char*)realloc(webpage_ptr->data, webpage_ptr->size*2);
    webpage_ptr->size*=2;
  }
  memcpy(webpage_ptr->data + webpage_ptr->len, buf, size * nmemb);
  webpage_ptr->len+=size*nmemb;
  // printf("%ld\n",webpage_ptr->len);
  return size * nmemb;
}

bool copyWebpage(const std::string &url, WebPage &webpage){
    // Your implementation goes here
    CURL* curl; //our curl object
    CURLcode status;
    cout<< "Requested URL: " <<url<<"\n";

    memset(&webpage, 0, sizeof(webpage));
    webpage.size = 1024;
    webpage.data = (char *)malloc(webpage.size);

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeResponse);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &webpage);

    status = curl_easy_perform(curl);

    if(status != CURLE_OK){
      cout<<"Curl fetch response failed\n";
      return false;
    }

    curl_easy_cleanup(curl);
    // cout << "Page data: " <<webpage.data << endl;
    // cout <<"page length:"<<webpage.len<< endl;
    return true;
}
class RPCServiceHandler : virtual public RPCServiceIf {
 private:
  string pageData;
  PageCache pageCahce;
  long cacheHitCount;
  long cacheQueryCount;
  double hitRatio; 
 public:
  RPCServiceHandler() {
    cacheHitCount = 0;
    cacheQueryCount = 0;
  }

  void getResponse(dataFormat& _return, const std::string& url) {

    WebPage webpage;

    bool cacheHit = pageCahce.getPage(url, webpage);
    if(!cacheHit) { 
      // cout<<"miss\n";
      bool status = copyWebpage(url, webpage);
      _return.isSucceeded = status; 
      // cout << "Page data: " <<webpage.data << endl;
      cout <<"page length:"<<webpage.len<< endl;
      if(_return.isSucceeded){
        _return.data = string(webpage.data,webpage.len);
        pageCahce.putPage(url,webpage);
      }
    }else{
      // cout<<"hit\n";
      _return.data = string(webpage.data,webpage.len);
      _return.isSucceeded = true;
      cacheHitCount++;
    }
    cacheQueryCount++;
    hitRatio = (double)cacheHitCount/ (double)cacheQueryCount;
    cout<<"Hit Ratio:"<<hitRatio<<"\n"; 
  }


};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<RPCServiceHandler> handler(new RPCServiceHandler());
  shared_ptr<TProcessor> processor(new RPCServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

