#include <glog/logging.h>



class ActionProducer {
public:
    // get actions by sequence, which will return the actions that are ready to be executed
    void getActions(u_int32_t seq);
    void produceActions();
};