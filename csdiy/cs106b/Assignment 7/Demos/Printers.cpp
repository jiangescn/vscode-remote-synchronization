#include "LinearProbingHashTable.h"
#include "RobinHoodHashTable.h"
#include <sstream>
using namespace std;

ostream& operator<< (ostream& out, LinearProbingHashTable::SlotType type) {
    string name = "<unknown slot type>";
    if (type == LinearProbingHashTable::SlotType::EMPTY)     name = "SlotType::EMPTY";
    if (type == LinearProbingHashTable::SlotType::FILLED)    name = "SlotType::FILLED";
    if (type == LinearProbingHashTable::SlotType::TOMBSTONE) name = "SlotType::TOMBSTONE";

    return out << name;
}

ostream& operator<< (ostream& out, LinearProbingHashTable::Slot slot) {
    ostringstream builder;
    builder << "{ " << quotedVersionOf(slot.value) << ", " << slot.type << " }";
    return out << builder.str();
}

bool operator== (const LinearProbingHashTable::Slot& lhs, const LinearProbingHashTable::Slot& rhs) {
    if (lhs.type != rhs.type) return false;

    /* 任何墓碑/空槽只与其他墓碑/空槽相等，忽略值。 */
    if (lhs.type == LinearProbingHashTable::SlotType::EMPTY ||
        lhs.type == LinearProbingHashTable::SlotType::TOMBSTONE) return true;

    return lhs.value == rhs.value;
}

ostream& operator<< (ostream& out, RobinHoodHashTable::Slot slot) {
    string distance;
    if (slot.distance >= 0) {
        distance = to_string(slot.distance);
    } else if (slot.distance == RobinHoodHashTable::EMPTY_SLOT) {
        distance = "EMPTY_SLOT";
    } else {
        distance = "<invalid distance: " + to_string(slot.distance) + ">";
    }

    ostringstream builder;
    builder << "{ " << quotedVersionOf(slot.value) << ", " << distance << " }";
    return out << builder.str();
}

bool operator== (const RobinHoodHashTable::Slot& lhs, const RobinHoodHashTable::Slot& rhs) {
    /* 如果任一为空，则仅当两者都为空时它们才相等。 */
    if (lhs.distance == RobinHoodHashTable::EMPTY_SLOT || rhs.distance == RobinHoodHashTable::EMPTY_SLOT) {
        return lhs.distance == rhs.distance;
    }

    /* 否则，只有真正相等时它们才相同。 */
    return lhs.distance == rhs.distance && lhs.value == rhs.value;
}
