#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "message.pb.h"

using namespace std;
using namespace google::protobuf;

class Server {
public:
    Server(int port) : port_(port), running_(false) {}

    void Start() {
        running_ = true;
        thread_ = std::thread(&Server::Run, this);
    }

    void Stop() {
        running_ = false;
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    void Run() {
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);

        // Creating socket file descriptor
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port_);

        // Forcefully attaching socket to the port 8080
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        while (running_) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("accept");
                continue;
            }

            handleClient(new_socket);
            close(new_socket);
        }

        close(server_fd);
    }

    void handleClient(int client_socket) {
        char buffer[1024] = {0};
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            return;
        }

        Request request;
        if (!request.ParseFromArray(buffer, valread)) {
            cerr << "Failed to parse request" << endl;
            return;
        }

        cout << "Received request: " << request.message() << endl;

        Response response;
        response.set_response("Hello, " + request.message());

        string serialized_response;
        if (!response.SerializeToString(&serialized_response)) {
            cerr << "Failed to serialize response" << endl;
            return;
        }

        write(client_socket, serialized_response.c_str(), serialized_response.size());
    }

    int port_;
    bool running_;
    std::thread thread_;
};

int main() {
    Server server(8080);
    server.Start();

    // Simulate server running for some time
    std::this_thread::sleep_for(std::chrono::seconds(60));

    server.Stop();
    return 0;
}