#include <node.h>

// 调用cubieboard的硬件控制库
extern "C"{
#include "gpio_lib.h"
}

// 定义一些工具宏
#define WIRING_DEFINE_CONSTANT(NAME, VALUE) (target)->Set( \
        v8::String::NewSymbol(NAME), \
        v8::Integer::New(VALUE), \
        static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete) \
);

#define PD1    SUNXI_GPD(1)
#define PD2    SUNXI_GPD(2)
#define PD3    SUNXI_GPD(3)
#define PD4    SUNXI_GPD(4)
#define PD5    SUNXI_GPD(5)
#define PD6    SUNXI_GPD(6)

#define PG0    SUNXI_GPG(0)
#define PG1    SUNXI_GPG(1)
#define PG2    SUNXI_GPG(2)
#define PG3    SUNXI_GPG(3)
#define PG4    SUNXI_GPG(4)
#define PG5    SUNXI_GPG(5)
#define PG6    SUNXI_GPG(6)
#define PG7    SUNXI_GPG(7)
#define PG8    SUNXI_GPG(8)
#define PG9    SUNXI_GPG(9)
#define PG10    SUNXI_GPG(10)
#define PG11    SUNXI_GPG(11)

#define PB18    SUNXI_GPB(18)
#define PB19    SUNXI_GPB(19)

using namespace v8;


// 初始化gpio的寄存器
Handle<Value> GPIO_init(const Arguments& args) {

    HandleScope scope;

    int32_t result;
    result = sunxi_gpio_init();

    if(result == SETUP_DEVMEM_FAIL){
	return ThrowException(
            Exception::TypeError(String::New("SETUP_DEVMEM_FAIL Error"))
        );
    }

    if(result == SETUP_MALLOC_FAIL){
        return ThrowException(
            Exception::TypeError(String::New("SETUP_MALLOC_FAIL Error"))
        );
    }

    if(result == SETUP_MMAP_FAIL){
        return ThrowException(
            Exception::TypeError(String::New("SETUP_MMAP_FAIL Error"))
        ); 
    }

    return scope.Close(Integer::New(SETUP_OK));
}


Handle<Value> GPIO_cleanup(const Arguments& args) {
    HandleScope scope;

    sunxi_gpio_cleanup();

    return scope.Close(Undefined());

}

// 获取引脚当状态 IN,OUT,PRE?
Handle<Value> GPIO_getcfg(const Arguments& args) {
    HandleScope scope;
    
    if (args.Length() < 1){
        return ThrowException(
            Exception::TypeError(String::New("Wrong number of arguments"))
        );
    }

    if (!args[0]->IsNumber()){
        return ThrowException(
             Exception::TypeError(String::New("Wrong arguments"))
        );
    }

    int32_t result;
    int32_t gpio = args[0]->ToInteger()->Value();

    result = sunxi_gpio_get_cfgpin(gpio);

    return scope.Close(Integer::New(result));
}

// 读取的电平状态 HIGH?LOW?
Handle<Value> GPIO_input(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 1){
        return ThrowException(
            Exception::TypeError(String::New("Wrong number of arguments"))
        );
    }

    if (!args[0]->IsNumber()){
        return ThrowException(
             Exception::TypeError(String::New("Wrong arguments"))
        );
    }

    int32_t result;
    int32_t gpio = args[0]->ToInteger()->Value();

    result = sunxi_gpio_input(gpio);

    if(result == -1){
        return ThrowException(
             Exception::TypeError(String::New("Reading pin failed"))
        );
    }

    return scope.Close(Integer::New(result));

}


// 输出电平
Handle<Value> GPIO_output(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2){
        return ThrowException(
            Exception::TypeError(String::New("Wrong number of arguments"))
        );	
    }

    if (!args[0]->IsNumber() || !args[1]->IsNumber()){
        return ThrowException(           
	     Exception::TypeError(String::New("Wrong arguments"))
        );
    }

    int32_t gpio = args[0]->ToInteger()->Value();
    int32_t value = args[1]->ToInteger()->Value();

    if( value != 0 && value != 1) {
        return ThrowException(                        
	     Exception::TypeError(String::New("Invalid output state"))
        );
    }

    if(sunxi_gpio_get_cfgpin(gpio) != SUNXI_GPIO_OUTPUT) {
	return ThrowException( 
             Exception::TypeError(String::New("Invalid output state"))
        );
    }

    sunxi_gpio_output(gpio, value);

    return scope.Close(Undefined());

}

// 设置GPIO功能 IN?OUT?PRE?
Handle<Value> GPIO_setcfg(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2){
        return ThrowException(
            Exception::TypeError(String::New("Wrong number of arguments"))
        );
    }

    if (!args[0]->IsNumber() || !args[1]->IsNumber()){
        return ThrowException(
             Exception::TypeError(String::New("Wrong arguments"))
        );
    }

    int32_t gpio = args[0]->ToInteger()->Value();
    int32_t direction = args[1]->ToInteger()->Value();

    if(direction != 0 && direction != 1 && direction != 2) {
        return ThrowException(
             Exception::TypeError(String::New("Invalid direction"))
        );
    }

    sunxi_gpio_set_cfgpin(gpio, direction);
    return scope.Close(Undefined());

}


void RegisterModule(Handle<Object> target) {

    NODE_SET_METHOD(target, "init", GPIO_init);
    NODE_SET_METHOD(target, "cleanup", GPIO_cleanup);
    NODE_SET_METHOD(target, "output", GPIO_output);
    NODE_SET_METHOD(target, "setcfg", GPIO_setcfg);
    NODE_SET_METHOD(target, "input", GPIO_input);
    NODE_SET_METHOD(target, "getcfg", GPIO_getcfg);

    WIRING_DEFINE_CONSTANT("HIGH", HIGH)
    WIRING_DEFINE_CONSTANT("LOW", LOW)
    WIRING_DEFINE_CONSTANT("PD1", PD1)
    WIRING_DEFINE_CONSTANT("PD2", PD2)
    WIRING_DEFINE_CONSTANT("PD3", PD3)
    WIRING_DEFINE_CONSTANT("PD4", PD4)
    WIRING_DEFINE_CONSTANT("PD5", PD5)
    WIRING_DEFINE_CONSTANT("PD6", PD6)

    WIRING_DEFINE_CONSTANT("PG0", PG0)
    WIRING_DEFINE_CONSTANT("PG1", PG1)
    WIRING_DEFINE_CONSTANT("PG2", PG2)
    WIRING_DEFINE_CONSTANT("PG3", PG3)
    WIRING_DEFINE_CONSTANT("PG4", PG4)
    WIRING_DEFINE_CONSTANT("PG5", PG5)
    WIRING_DEFINE_CONSTANT("PG6", PG6)
    WIRING_DEFINE_CONSTANT("PG7", PG7)
    WIRING_DEFINE_CONSTANT("PG8", PG8)
    WIRING_DEFINE_CONSTANT("PG9", PG9)
    WIRING_DEFINE_CONSTANT("PG10", PG10)
    WIRING_DEFINE_CONSTANT("PG11", PG11)

    WIRING_DEFINE_CONSTANT("PB18", PB18)
    WIRING_DEFINE_CONSTANT("PB19", PB19)

    WIRING_DEFINE_CONSTANT("IN", INPUT)
    WIRING_DEFINE_CONSTANT("OUT", OUTPUT)
    WIRING_DEFINE_CONSTANT("PER", PER)
}

NODE_MODULE(gpio, RegisterModule);
