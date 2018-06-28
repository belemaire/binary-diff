#include <node.h>
#include <node_buffer.h>

#include <memory.h>
#include <stdlib.h>
#include <nan.h>

extern "C" {
  #include "bsdiff/bsdiff.h" 
}

namespace bsdpNode {
  using namespace v8;

  NAN_METHOD(diff) {
    Nan::EscapableHandleScope scope;
    Isolate* isolate = info.GetIsolate();
   
    char* oldBuffer   = (char*)node::Buffer::Data(info[0]->ToObject());
    int oldBufferSize = info[1]->Uint32Value();
    char* newBuffer   = (char*)node::Buffer::Data(info[2]->ToObject());
    int newBufferSize = info[3]->Uint32Value();

    SizedCharArray* result = (SizedCharArray*)malloc(sizeof(SizedCharArray));
    result->value = NULL;
    result->size = 0;

    char error[1024];
    int ret = bsdiff(error, oldBuffer, oldBufferSize, newBuffer, newBufferSize, result);  

    if(ret != 0) {
      free(result);
      isolate->ThrowException(Exception::Error(
                String::NewFromUtf8(isolate, error)));
    }   

    v8::Local<v8::Object> buf = Nan::NewBuffer(result->size).ToLocalChecked();
    char* pbuf = node::Buffer::Data(buf);
    memcpy(pbuf, result->value, result->size);
    free(result);

    info.GetReturnValue().Set(buf);
  }

  NAN_MODULE_INIT(init) {
    Nan::Set(target
      ,Nan::New<v8::String>("diff").ToLocalChecked()
      ,Nan::New<v8::FunctionTemplate>(diff)->GetFunction());
  }

  NODE_MODULE(bsdp, init)
}