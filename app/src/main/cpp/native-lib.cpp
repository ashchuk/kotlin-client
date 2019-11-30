#include <jni.h>
#include <string>
#include "json.h"

extern "C" JNIEXPORT jstring


JNICALL
Java_com_ashchuk_clientapp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    using json = nlohmann::json;


    // create object from string literal
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    // or even nicer with a raw string literal
    auto j2 = R"(
    {
        "happy": true,
        "pi": 3.141
    }
    )"_json;

    // parse explicitly
    auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");

    // explicit conversion to string
    std::string s = j.dump();    // {\"happy\":true,\"pi\":3.141}
    // serialization with pretty printing
    // pass in the amount of spaces to indent
    std::string test1 = j.dump(4);
    // {
    //     "happy": true,
    //     "pi": 3.141
    // }

    // store a string in a JSON value
    json j_string = "this is a string";
    // retrieve the string value
    auto cpp_string = j_string.get<std::string>();
    // retrieve the string value (alternative when an variable already exists)
    std::string cpp_string2;
    j_string.get_to(cpp_string2);
    // retrieve the serialized value (explicit JSON serialization)
    std::string serialized_string = j_string.dump();
    // output of original string
    std::string test2 = j_string.get<std::string>();
    // output of serialized value
    std::string test3 = serialized_string;

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
