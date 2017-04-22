#include "Registration.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "Registration.pb.h"
#pragma clang diagnostic pop

Registration::Registration(const void *data, int size) {
    deserialize(data, size);
}

void Registration::serialize(std::string *output) {
    RegistrationProto registrationProto;
    registrationProto.set_type(type);
    registrationProto.set_clientid(clientId);
    registrationProto.set_endpoint(endpoint);
    registrationProto.SerializeToString(output);
}

void Registration::deserialize(const void *data, int size) {
    RegistrationProto registrationProto;
    registrationProto.ParseFromArray(data, size);
    type = static_cast<Type>(registrationProto.type());
    clientId = registrationProto.clientid();
    strncpy(endpoint, registrationProto.endpoint().c_str(), sizeof(endpoint));
}

bool Registration::operator==(const Registration &other) {
    return type == other.type && clientId == other.clientId;
}

// static
int Registration::protoSize() {
    RegistrationProto registrationProto;
    return registrationProto.ByteSize();
}


