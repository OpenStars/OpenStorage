// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "RawBigSetKVService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::bskv;

class RawBigSetKVServiceHandler : virtual public RawBigSetKVServiceIf {
 public:
  RawBigSetKVServiceHandler() {
    // Your initialization goes here
  }

  void bsgPutItem(TPutItemResult& _return, const TContainerKey rootID, const TItem& item) {
    // Your implementation goes here
    printf("bsgPutItem\n");
  }

  bool bsgRemoveItem(const TMetaKey key, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("bsgRemoveItem\n");
  }

  void bsgExisted(TExistedResult& _return, const TContainerKey rootID, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("bsgExisted\n");
  }

  void bsgGetItem(TItemResult& _return, const TContainerKey rootID, const TItemKey& itemKey) {
    // Your implementation goes here
    printf("bsgGetItem\n");
  }

  void bsgGetSlice(TItemSetResult& _return, const TContainerKey rootID, const int32_t fromIdx, const int32_t count) {
    // Your implementation goes here
    printf("bsgGetSlice\n");
  }

  void bsgGetSliceFromItem(TItemSetResult& _return, const TContainerKey rootID, const TItemKey& fromKey, const int32_t count) {
    // Your implementation goes here
    printf("bsgGetSliceFromItem\n");
  }

  void bsgGetSliceR(TItemSetResult& _return, const TContainerKey rootID, const int32_t fromIdx, const int32_t count) {
    // Your implementation goes here
    printf("bsgGetSliceR\n");
  }

  void bsgGetSliceFromItemR(TItemSetResult& _return, const TContainerKey rootID, const TItemKey& fromKey, const int32_t count) {
    // Your implementation goes here
    printf("bsgGetSliceFromItemR\n");
  }

  void bsgRangeQuery(TItemSetResult& _return, const TContainerKey rootID, const TItemKey& startKey, const TItemKey& endKey) {
    // Your implementation goes here
    printf("bsgRangeQuery\n");
  }

  void bsgMultiPut(TMultiPutItemResult& _return, const TContainerKey rootID, const TItemSet& setData, const bool getAddedItems, const bool getReplacedItems) {
    // Your implementation goes here
    printf("bsgMultiPut\n");
  }

  int64_t getTotalCount(const TContainerKey rootID) {
    // Your implementation goes here
    printf("getTotalCount\n");
  }

  int64_t removeAll(const TContainerKey rootID) {
    // Your implementation goes here
    printf("removeAll\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<RawBigSetKVServiceHandler> handler(new RawBigSetKVServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new RawBigSetKVServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

