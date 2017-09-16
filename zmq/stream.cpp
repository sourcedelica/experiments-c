#include <cstring>
#include "zmq.hpp"


int main (int argc, char *argv [])
{
    bool verbose = false;
    int argn;
    for (argn = 1; argn < argc; argn++) {
        if (strcmp(argv [argn], "--help") == 0 || strcmp(argv [argn], "-h") == 0) {
            puts ("echoserver [options] ...");
            puts ("  --verbose / -v         verbose test output");
            puts ("  --help / -h            this information");
            return 0;
        }
        else
        if (strcmp(argv [argn], "--verbose") == 0 ||  strcmp(argv [argn], "-v") == 0)
            verbose = true;
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }
    zmq::context_t ctx;
    zmq::socket_t socket(ctx, ZMQ_STREAM);
    assert(socket);
    socket.connect("tcp://localhost:1111");

    uint8_t id[256];
    size_t id_size = 256;
    uint8_t data[1024];
    size_t data_size = 1024;
    size_t received;
    zmq::message_t dataMsg;

    id_size = socket.recv(id, id_size, 0);
    assert(id_size > 0);
    zmq::message_t idMsg(id, id_size);

//    socket.recv(&idMsg);
//    assert(idMsg.size() > 0);
    socket.recv(&dataMsg);
    assert(dataMsg.size() == 0);

//    socket.send(id, id_size, ZMQ_SNDMORE);
    socket.send(idMsg, ZMQ_SNDMORE);
    zmq::message_t msg1("12345", 5);
    socket.send(msg1, ZMQ_SNDMORE);

//    socket.send(id, id_size, ZMQ_SNDMORE);
    socket.send(idMsg, ZMQ_SNDMORE);
    zmq::message_t msg2("67890", 5);
    socket.send(msg2, ZMQ_SNDMORE);

//    socket.send(id, id_size, ZMQ_SNDMORE);
    socket.send(idMsg, ZMQ_SNDMORE);
    zmq::message_t msg3("abcde", 5);
    socket.send(msg3, ZMQ_SNDMORE);

    socket.send("", 0);

    return 0;
}