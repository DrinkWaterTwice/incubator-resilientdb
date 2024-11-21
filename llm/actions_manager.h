#include <iostream>
#include "platform/statistic/stats.h"

// 负责动作的生成、以及状态处理

using namespace resdb;
using namespace std;

namespace controller{
class ActionProducer {
    public:

    
    // 获取全局唯一的 ActionProducer 实例
    static ActionProducer& GetInstance();
    
    // 删除拷贝构造函数和赋值操作符
    vector<int64_t> getActions(int64_t seq);

    void produceActions();
    
    private:
        Stats* stats_;
     
        ActionProducer();
        };
}


