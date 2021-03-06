// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "TIBSDataService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::bskv;

class TIBSDataServiceHandler : virtual public TIBSDataServiceIf {
 public:
  TIBSDataServiceHandler() {
    // Your initialization goes here
  }

  void putItem(TPutItemResult& _return, const TKey bigsetID, const TItem& item) {
    // Your implementation goes here
    printf("putItem\n");
  }

  bool removeItem(const TKey bigsetID, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("removeItem\n");
  }

  void existed(TExistedResult& _return, const TKey bigsetID, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("existed\n");
  }

  void getItem(TItemResult& _return, const TKey bigsetID, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("getItem\n");
  }

  void getSlice(TItemSetResult& _return, const TKey bigsetID, const int32_t fromPos, const int32_t count) {
    // Your implementation goes here
    printf("getSlice\n");
  }

  void getSliceFromItem(TItemSetResult& _return, const TKey bigsetID, const TItemKey& fromKey, const int32_t count) {
    // Your implementation goes here
    printf("getSliceFromItem\n");
  }

  void getSliceR(TItemSetResult& _return, const TKey bigsetID, const int32_t fromPos, const int32_t count) {
    // Your implementation goes here
    printf("getSliceR\n");
  }

  void getSliceFromItemR(TItemSetResult& _return, const TKey bigsetID, const TItemKey& fromKey, const int32_t count) {
    // Your implementation goes here
    printf("getSliceFromItemR\n");
  }

  void rangeQuery(TItemSetResult& _return, const TKey bigsetID, const TItemKey& startKey, const TItemKey& endKey) {
    // Your implementation goes here
    printf("rangeQuery\n");
  }

  void multiPut(TMultiPutItemResult& _return, const TKey bigsetID, const TItemSet& setData, const bool getAddedItems, const bool getReplacedItems) {
    // Your implementation goes here
    printf("multiPut\n");
  }

  int64_t getTotalCount(const TKey bigsetID) {
    // Your implementation goes here
    printf("getTotalCount\n");
  }

  int64_t removeAll(const TKey bigsetID) {
    // Your implementation goes here
    printf("removeAll\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<TIBSDataServiceHandler> handler(new TIBSDataServiceHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new TIBSDataServiceProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

