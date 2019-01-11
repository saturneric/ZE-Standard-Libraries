#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

__CALLBACK_DEFINE(calStandardDataCTN){
    uint32_t size = __ARGS(0, uint32_t);
    size += 64;
    //unsigned long long temp = __NOW_INDEX;
    if(__NOW_INDEX == __LIST_LEN - 1){
        __RETURN("%ull", size);
    }
    return __CRETURN__;
}
