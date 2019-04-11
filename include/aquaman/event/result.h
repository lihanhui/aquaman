#ifndef AQUAMAN_EVENT_RESULT
#define AQUAMAN_EVENT_RESULT

#include <string>
namespace aquman
{
namespace event
{
template <typename V> class result {
private:
    int code;
    std::string err_msg;
	V value;

private:
    result(){
    	this->code = 0;
    	this->err_msg = "";
    }
public: 
	/*result(result && v): code(v.code), err_msg(v.err_msg), value(v.value) {
        
    }//*/
    result(V value){ 
    	this->code = 0;
    	this->err_msg = "";
    	this->value = value;
    }
    
    result(int code, std::string & err_msg){
        this->code = code;
    	this->err_msg = err_msg;
    }
    
    int get_code(){
    	return code;
    } 
    
    std::string & get_err_msg(){
    	return err_msg;
    }
    
    V & get_value(){
    	return value;
    }
};
}; // namespace event
}; // namespace aquman
#endif
