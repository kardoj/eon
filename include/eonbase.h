#ifndef EON_EONBASE_H
#define EON_EONBASE_H

#include <string>
#include <vector>

class EonBase {
    public:
        EonBase();
        virtual ~EonBase();
        std::vector<std::string> get_messages();
        void add_message(const std::string message);

    private:
        std::vector<std::string> messages;
};


#endif //EON_EONBASE_H
