#include "eonbase.h"

using namespace std;

EonBase::EonBase() {}
EonBase::~EonBase() {}

vector<string> EonBase::get_messages()
{
    return this->messages;
}

void EonBase::add_message(const string message)
{
    this->messages.push_back(message);
}

void EonBase::add_messages(const vector<string> messages)
{
    unsigned size = messages.size();
    if (size == 0) return;

    for (unsigned i = 0; i < size; i++)
    {
        this->messages.push_back(messages.at(i));
    }
}
