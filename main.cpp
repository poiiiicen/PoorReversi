#include <iostream>
#include <cpr/cpr.h>
#include <exception>
#include "MCT.h"

const std::string SESSION_ID = "7";
const std::string SERVER = "http://47.89.179.202:5000";
const std::string CREATE_SESSION = "/create_session/" + SESSION_ID;
const std::string GET_TURN = "/turn/" + SESSION_ID;
const std::string GET_BOARD = "/board_string/" + SESSION_ID;
const std::string POST_MOVE = "/move/" + SESSION_ID;

std::string get_response(std::string URL) {
    auto res = cpr::Get(cpr::Url{std::move(URL)});
    if (res.status_code != 200) {
        return res.text;
    }
    // Throw Exception
}

std::string post_response(std::string URL) {
    auto res = cpr::Post(cpr::Url{std::move(URL)});
    if (res.status_code != 200) {
        throw std::exception();
    }
    return res.text;
    // Throw Exception
}

std::string get_player() {
    auto res = get_response(SERVER + CREATE_SESSION);
    if (res.length() == 1 && res == "W" || res == "B") {
        return res;
    }
    return "";
}

std::string get_turn() {
    auto res = get_response(SERVER + GET_TURN);
    if (res.length() == 1 && res == "W" || res == "B") {
        return res;
    }
    return "";
}

void decode_board(std::string origin_board, int board[8][8]) {
    for (auto i = 0; i != 8; ++i) {
        for (auto j = 0; j != 8; ++j) {
            board[i][j] = origin_board[i * 16 + j * 2] == '0' ? 0 : origin_board[i * 16 + j * 2] == 'W' ? 2 : 1;
        }
    }
}

bool move(MCT &mct, std::string player) {
    auto res = get_response(SERVER + GET_BOARD);
    int board[8][8] = {0};
    decode_board(res, board);
    auto pos = mct.updateMCT(board);
    if (pos.first == -1)
        return true;
    if (pos.second == -1)
        return false;
    res = post_response(
            SERVER + POST_MOVE + "/" + std::to_string(pos.first) + "/" + std::to_string(pos.second) + "/" + player);
    if (res == "ERROR") {
        std::cout << "Unexpected Move" << std::endl;
    }
    return true;
}

int main() {
    const auto player = get_player();
    MCT mct;
    if (player.empty()) {
        std::cout << "Unexpected Player" << std::endl;
        return 1;
    }
    mct.createMCT(player == "B");
    while (true) {
        if (get_turn() != player) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }
        if (!move(mct, player)) {
            break;
        }
    }
    return 0;
}