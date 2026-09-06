
SocketClient client;

int startClient();
bool isConnected();
void stopClient();
bool initServer();
bool stopServer();

enum Mode {
    InitMode = 1,
    HackMode = 2,
    StopMode = 98,
    EspMode = 99,
};

struct Request {
    int Mode;
    bool boolean;
    float FOV;
    int ScreenWidth;
    int ScreenHeight;
    uint64_t playerPtr;
};

#define maxplayerCount 60
struct PlayerData {
    Vector3 headPosition;
    Vector3 bottomPlayerPosition;

    float health;
    char name[2000];
    bool isDieing;
    bool isBot;
    bool isInVehicle;

    float distance;
    uint64_t playerPtr;
};

struct Response {
    bool Success;
    int PlayerCount;
    PlayerData Players[maxplayerCount];
    int matchAlive;           // 1 = in match, 0 = not
    int remainingTimeSeconds; // 190..0 when in match, -1 when not
};

int startClient(){
    client = SocketClient();
    if (!client.Create()) {
        return -1;
    }
    if (!client.Connect()) {
        return -1;
    }
    if (!initServer()) {
        return -1;
    }
    LOGI("Start Client");
    return 0;
}

bool isConnected(){
    return client.connected;
}

void stopClient() {
    if(client.created && isConnected()){
        stopServer();
        client.Close();
    }
}

bool initServer() {
    Request request{Mode::InitMode, true, 0};
    int code = client.send((void*) &request, sizeof(request));
    if(code > 0) {
        Response response{};
        size_t length = client.receive((void*) &response);
        if(length > 0) {
            return response.Success;
        }
    }
    return false;
}

bool stopServer() {
    Request request{Mode::StopMode};
    int code = client.send((void*) &request, sizeof(request));
    if(code > 0) {
        Response response{};
        size_t length = client.receive((void*) &response);
        if(length > 0) {
            return response.Success;
        }
    }
    return false;
}

bool SendFeatuere(int32_t func, bool ftr) {
    Request request{func, ftr};
    int code = client.send((void*) &request, sizeof(request));
    if (code > 0) {
        Response response{};
        size_t length = client.receive((void*) &response);
        if (length > 0) {
            return response.Success;
        }
    }
    return false;
}

bool SendFOV(int32_t func,int ftr) {
    Request request{func, false, ftr, 0};
    int code = client.send((void*) &request, sizeof(request));
    if (code > 0) {
        Response response{};
        size_t length = client.receive((void*) &response);
        if (length > 0) {
            return response.Success;
        }
    }
    return false;
}

bool LockSpecificPlayer(uint64_t ptr) {
    Request request{525, false, 0, 0, 0, ptr};
    int code = client.send((void*) &request, sizeof(request));
    if (code > 0) {
        Response response{};
        size_t length = client.receive((void*) &response);
        if (length > 0) {
            return response.Success;
        }
    }
    return false;
}


Response getData(int screenWidth, int screenHeight){
    Request request{Mode::EspMode,  0.0f,0.0f, screenWidth, screenHeight};
    int code = client.send((void*) &request, sizeof(request));
    if(code > 0){
        Response response{};
        size_t length = client.receive((void*) &response);
        if(length > 0){
            return response;
        }
    }
    Response response{false, 0};
    return response;
}

