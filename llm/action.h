#include <iostream>
#include <string>
#include <list>


// 定义一个枚举类，表示节点动作
class NodeAction {
public:
    enum Action {
        NormalSend,
        DelayedSend,
        PartitonSend,
        Discard
    };

    // 构造函数
    NodeAction(Action action, int timeMs)
        : action_(action), timeMs_(timeMs) {}

    // 获取动作
    Action getAction() const {
        return action_;
    }

    // 获取时间（毫秒）
    int getTimeMs() const {
        return timeMs_;
    }

    // 获取动作的字符串表示
    static std::string name(Action action) {
        switch (action) {
            case NormalSend: return "NormalSend";
            case DelayedSend: return "DelayedSend";
            case PartitonSend: return "PartitonSend";
            case Discard: return "Discard";
            default: return "Unknown";
        }
    }

private:
    Action action_;
    int timeMs_;
};

// 重载输出流操作符，方便打印
std::ostream& operator<<(std::ostream& os, const NodeAction& action) {
    os << NodeAction::name(action.getAction()) << " (" << action.getTimeMs() << " ms)";
    return os;
}


// 定义一个链表节点类
class NodeActionList {
public:
    // 添加一个动作到链表
    void addAction(const NodeAction& action) {
        actions_.push_back(action);
    }

    // 获取所有动作
    const std::list<NodeAction>& getActions() const {
        return actions_;
    }

private:
    std::list<NodeAction> actions_;
};