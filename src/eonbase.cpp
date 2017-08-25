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
