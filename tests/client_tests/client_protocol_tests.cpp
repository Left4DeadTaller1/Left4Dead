/*#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "client_protocol.h"
#include "socket.h"

class MockSocket : public Socket {
public:
    MockSocket(const char* servname) : Socket(servname) {}
    MockSocket(const char* hostname, const char* servname) : Socket(hostname, servname) {}

    MOCK_METHOD3(sendall, int(const void* data, unsigned int sz, bool* was_closed));
    MOCK_METHOD3(recvall, int(void* data, unsigned int sz, bool* was_closed));
};


TEST(ClientProtocolTest, ReceiveCreateOrJoinTest) {
    uint16_t expectedCode = 42;
    bool wasClosed = false;

    Socket socket("4085");
    MockSocket mockSocketclient("127.0.0.1", "4085");

    socket.sendall(&expectedCode, 2, &wasClosed);

    ClientProtocol clientProtocol(mockSocketclient);

    int result = clientProtocol.receiveCreateorJoin(wasClosed);

    EXPECT_FALSE(wasClosed);
    EXPECT_EQ(result, expectedCode);
}
*/


