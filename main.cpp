#include <iostream>
#include <cpr/cpr.h>
#include "MCT.h"
#include "exceptions.h"

#define DEBUG

const std::string SESSION_ID = "47";
const std::string SERVER = "http://47.89.179.202:5000";
const std::string CREATE_SESSION = "/create_session/" + SESSION_ID;
const std::string GET_TURN = "/turn/" + SESSION_ID;
const std::string GET_BOARD = "/board_string/" + SESSION_ID;
const std::string POST_MOVE = "/move/" + SESSION_ID;

std::string get_response(std::string URL) {
    auto res = cpr::Get(cpr::Url{std::move(URL)});
    if (res.status_code != 200) {
        throw StatusCodeException(res.status_code);
    }
    return res.text;
}

std::string post_response(std::string URL) {
    auto res = cpr::Post(cpr::Url{std::move(URL)});
    if (res.status_code != 200) {
        throw StatusCodeException(res.status_code);
    }
    return res.text;
}

std::string get_player() {
    std::string res;
    try {
        res = get_response(SERVER + CREATE_SESSION);
    }
    catch (StatusCodeException &e) { std::cout << e.what() << " " << e.get_status_code() << std::endl; }
    if (res.length() != 1 || res != "W" && res != "B") {
        throw PlayerException();
    }
    return res;
}

std::string get_turn() {
    std::string res;
    try {
        res = get_response(SERVER + GET_TURN);
    }
    catch (StatusCodeException &e) { std::cout << e.what() << " " << e.get_status_code() << std::endl; }
    if (res.length() != 1 || res != "W" && res != "B") {
        throw TurnException();
    }
    return res;
}

void decode_board(std::string origin_board, int board[8][8]) {
    for (auto i = 0; i != 8; ++i) {
        for (auto j = 0; j != 8; ++j) {
            board[i][j] = origin_board[i * 16 + j * 2] == '0' ? 0 : origin_board[i * 16 + j * 2] == 'W' ? 2 : 1;
        }
    }
}

bool move(MCT &mct, const std::string &player) {
    std::string res;
    try {
        res = get_response(SERVER + GET_BOARD);
    }
    catch (StatusCodeException &e) { std::cout << e.what() << " " << e.get_status_code() << std::endl; }

    int board[8][8] = {0};
    try {
        decode_board(res, board);
    }
    catch (BoardException &e) {
        std::cout << e.what() << std::endl;
        return false;
    }

#ifdef DEBUG
    for (int i = 0; i != 8; ++i) {
        for (int j = 0; j != 8; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
#endif

    auto pos = mct.updateMCT(board);

#ifdef DEBUG
    std::cout << pos.first << " " << pos.second << std::endl;
#endif

    if (pos.first == -1)
        return true;
    if (pos.second == -1)
        return false;
    res = post_response(
            SERVER + POST_MOVE + "/" + std::to_string(pos.first) + "/" + std::to_string(pos.second) + "/" + player);
    if (res == "ERROR") {
        throw MoveException();
    }
    return true;
}

int main() {
    std::string player;
    try {
        player = get_player();
    }
    catch (PlayerException &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    MCT mct;

#ifdef DEBUG
    std::cout << player << std::endl;
#endif

    mct.createMCT(player == "B");
    while (true) {
        try {
            if (get_turn() != player) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
        }
        catch (TurnException &e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
        try {
            if (!move(mct, player)) {
                break;
            }
        }
        catch (MoveException &e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
