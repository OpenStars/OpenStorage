// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "TStringBigSetKVService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::bskv;

class TStringBigSetKVServiceHandler : virtual public TStringBigSetKVServiceIf {
 public:
  TStringBigSetKVServiceHandler() {
    // Your initialization goes here
  }

  void bsPutItem(TPutItemResult& _return, const TStringKey& bsName, const TItem& item) {
    // Your implementation goes here
    printf("bsPutItem\n");
  }

  bool bsRemoveItem(const TStringKey& bsName, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("bsRemoveItem\n");
  }

  void bsExisted(TExistedResult& _return, const TStringKey& bsName, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("bsExisted\n");
  }

  void bsGetItem(TItemResult& _return, const TStringKey& bsName, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("bsGetItem\n");
  }

  void bsGetSlice(TItemSetResult& _return, const TStringKey& bsName, const int32_t fromPos, const int32_t count) {
    // Your implementation goes here
    printf("bsGetSlice\n");
  }

  void bsGetSliceFromItem(TItemSetResult& _return, const TStringKey& bsName, const TItemKey& fromKey, const int32_t count) {
    // Your implementation goes here
    printf("bsGetSliceFromItem\n");
  }

  void bsGetSliceR(TItemSetResult& _return, const TStringKey& bsName, const int32_t fromPos, const int32_t count) {
    // Your implementation goes here
    printf("bsGetSliceR\n");
  }

  void bsGetSliceFromItemR(TItemSetResult& _return, const TStringKey& bsName, const TItemKey& fromKey, const int32_t count) {
    // Your implementation goes here
    printf("bsGetSliceFromItemR\n");
  }

  void bsRangeQuery(TItemSetResult& _return, const TStringKey& bsName, const TItemKey& startKey, const TItemKey& endKey) {
    // Your implementation goes here
    printf("bsRangeQuery\n");
  }

  void bsMultiPut(TMultiPutItemResult& _return, const TStringKey& bsName, const TItemSet& setData, const bool getAddedItems, const bool getReplacedItems) {
    // Your implementation goes here
    printf("bsMultiPut\n");
  }

  int64_t getTotalCount(const TStringKey& bsName) {
    // Your implementation goes here
    printf("getTotalCount\n");
  }

  int64_t removeAll(const TStringKey& bsName) {
    // Your implementation goes here
    printf("removeAll\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<TStringBigSetKVServiceHandler> handler(new TStringBigSetKVServiceHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new TStringBigSetKVServiceProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

