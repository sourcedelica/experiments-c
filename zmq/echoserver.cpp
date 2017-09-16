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
    assert (socket);
    int bound = zmq_bind (socket, "tcp://*:1111");
    assert (bound == 0);
    uint8_t id [256];
    size_t id_size = 256;
    uint8_t data [1024];
    size_t data_size = 1024;
    size_t received;

    while(3) {
        id_size = socket.recv(id, id_size, 0);
        assert (id_size > 0);
        do {
            received = socket.recv(data, data_size, 0);
            assert (received >= 0);
            if (received >0) {
                socket.send(id, id_size, ZMQ_SNDMORE);
                socket.send(data, received, ZMQ_SNDMORE);
            }
        } while (received == data_size);
    }

    return 0;
}