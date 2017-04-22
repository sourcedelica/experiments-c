#include "PingPong.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "PingPong.pb.h"
#pragma clang diagnostic pop

bool PingPong::operator==(const PingPong &other) {
    return type == other.type && clientId == other.clientId;
}

PingPong::PingPong(const void *data, int size) {
    deserialize(data, size);
}

void PingPong::serialize(std::string *output) {
    PingPongProto pingPongProto;
    pingPongProto.set_type(type);
    pingPongProto.set_clientid(clientId);
    pingPongProto.SerializeToString(output);
}

void PingPong::deserialize(const void *data, int size) {
    PingPongProto pingPongProto;
    pingPongProto.ParseFromArray(data, size);
    type = static_cast<Type>(pingPongProto.type());
    clientId = pingPongProto.clientid();
}

// static
int PingPong::protoSize() {
    PingPongProto pingPongProto;
    return pingPongProto.ByteSize();
}
