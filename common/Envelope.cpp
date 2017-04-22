#include "Envelope.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "Envelope.pb.h"
#pragma clang diagnostic pop

Envelope::Envelope(long correlationId, int clientId, int type, long timeoutMs, bool oneWay)
        : correlationId(correlationId),
          clientId(clientId),
          type(type),
          timeoutMs(timeoutMs),
          oneWay(oneWay) {}

Envelope::Envelope(const void *data, int size) {
    deserialize(data, size);
}

Envelope::Envelope(const Envelope &other)
        : correlationId(other.correlationId),
          clientId(other.clientId),
          type(other.type),
          timeoutMs(other.timeoutMs),
          oneWay(other.oneWay) {}


bool Envelope::operator==(const Envelope &other) {
    return correlationId == other.correlationId && clientId == other.clientId &&
           type == other.type && oneWay == other.oneWay;
}

void Envelope::serialize(std::string *output) const {
    EnvelopeProto envelopeProto;
    envelopeProto.set_correlationid(correlationId);
    envelopeProto.set_clientid(clientId);
    envelopeProto.set_type(type);
    envelopeProto.set_timeoutms(timeoutMs);
    envelopeProto.set_oneway(oneWay);
    envelopeProto.SerializeToString(output);
}

void Envelope::deserialize(const void *data, int size) {
    EnvelopeProto envelopeProto;
    envelopeProto.ParseFromArray(data, size);
    correlationId = envelopeProto.correlationid();
    clientId = envelopeProto.clientid();
    type = envelopeProto.type();
    timeoutMs = envelopeProto.timeoutms();
    oneWay = envelopeProto.oneway();
}

// static
int Envelope::protoSize() {
    EnvelopeProto envelopeProto;
    return envelopeProto.ByteSize();
}

