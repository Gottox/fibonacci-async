#include <v8.h>
#include <node.h>
#include <map>

using namespace v8;
using namespace node;

static void background(uv_work_t *req);
static void after(uv_work_t *req);

struct FibData {
	int input;
	Persistent<Function> cb;
	int result;
};

static Handle<Value> Fibonacci(const Arguments& args) {
  HandleScope scope;
  const char *usage = "usage: fibonacci(x, cb)";
  if (args.Length() != 2) {
    return ThrowException(Exception::Error(String::New(usage)));
  }

  FibData *data = (FibData *)malloc(sizeof(struct FibData));

  Local<Function> cb = Local<Function>::Cast(args[1]);
  data->cb = Persistent<Function>::New(cb);
  data->input = args[0]->Int32Value();

  uv_work_t *req = (uv_work_t *) (calloc(1, sizeof(uv_work_t)));
  req->data = data;

  uv_queue_work(uv_default_loop(), req,
		  background,
		  after);
  ev_ref(EV_DEFAULT_UC);
  return Undefined();

}

static void background(uv_work_t *req){
  struct FibData * data = (struct FibData *)req->data;

  int i, num1 = 0, num2 = 1, result = 1;
  for (i = 1; i < data->input; i++) {
    result = num1 + num2;
    num1 = num2;
    num2 = result;
  }

  data->result = result;
}

static void after(uv_work_t *req) {
  HandleScope scope;
  ev_unref(EV_DEFAULT_UC);
  struct FibData *data = (struct FibData *)req->data;
  Local<Value> argv[] = {
    Integer::New(data->result)
  };
  TryCatch try_catch;
  data->cb->Call(Context::GetCurrent()->Global(), 1, argv);
  if (try_catch.HasCaught()) {
    FatalException(try_catch);
  }
  data->cb.Dispose();
  free(data);
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;

  NODE_SET_METHOD(target, "fibonacci", Fibonacci);
}
