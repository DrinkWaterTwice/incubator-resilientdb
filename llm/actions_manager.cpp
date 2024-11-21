#include <iostream>
// #include "action.h"
#include "actions_manager.h"
#include "platform/statistic/stats.h"

using namespace controller;
// 负责动作的生成、以及状态处理

    


ActionProducer& ActionProducer::GetInstance() {
    static ActionProducer instance;
    return instance;
}

// 公有成员函数
std::vector<int64_t> ActionProducer::getActions(int64_t seq) {
    std::vector<int64_t> delays = {1, 1, 1, 1, 1, 1, 1};
    return delays;
}

void ActionProducer::produceActions() {
    // 实现逻辑
}

// 私有构造函数
ActionProducer::ActionProducer() {
    stats_ = Stats::GetGlobalStats();
}

