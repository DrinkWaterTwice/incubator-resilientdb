#include <iostream>
#include "action.h"
#include "actions_producer.h"


class ActionProducer {
public:
    void getActions(u_int32_t seq);
    void produceActions();
};