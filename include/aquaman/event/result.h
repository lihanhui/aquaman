#ifndef AQUAMAN_EVENT_RESULT
#define AQUAMAN_EVENT_RESULT

#include <string>
namespace aquaman
{

template <typename V> class result {
private:
    int code;
    std::string err_msg;
	std::shared_ptr<V> value;

private:
    result(){
    	this->code = 0;
    	this->err_msg = "";
    }
public: 
	/*result(result && v): code(v.code), err_msg(v.err_msg), value(v.value) {
        
    }//*/
    result(std::shared_ptr<V> value)
    {
        this->code = 0;
    	this->err_msg = "";
    	this->value = value;
    }
    
    result(int code, const std::string & err_msg){
        this->code = code;
    	this->err_msg = err_msg;
    }

    const int get_code() const
    {
        return code;
    }

    const std::string &get_err_msg() const
    {
        return err_msg;
    }

    const std::shared_ptr<V> get_value() const
    {
        return value;
    }
};

}; // namespace aquaman
#endif
