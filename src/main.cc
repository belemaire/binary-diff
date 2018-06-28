#include <node.h>
#include <node_buffer.h>

#include <memory.h>
#include <stdlib.h>
#include <nan.h>

extern "C" {
  #include "bsdiff/bsdiff.h" 
}

namespace bsdpNode {
  using namespace Nan;
  using namespace v8;

  void diffBuffer(const v8::FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);

    char* oldBuffer = (char*) node::Buffer::Data(args[0]->ToObject());
    int oldBufferSize = args[1]->Uint32Value();
    char* newBuffer = (char*) node::Buffer::Data(args[2]->ToObject());
    int newBufferSize = args[3]->Uint32Value();
    String::Utf8Value patchfile(args[4]);
   
    char error[1024];
    int ret = bsdiffBuffer(error, oldBuffer, oldBufferSize, newBuffer, newBufferSize, *patchfile);   
    if(ret != 0) {
      isolate->ThrowException(Exception::Error(
                        String::NewFromUtf8(isolate, error)));
    }    
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "diffBuffer", diffBuffer);
  }

  NODE_MODULE(bsdp, init)
}