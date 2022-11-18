/*
 * This is a vitally important site to refer to for terminal escape sequences: https://en.wikipedia.org/wiki/ANSI_escape_code#OSC
 */


#include <stdlib.h>
#include <iostream>
#include <tuple>
#include <string>
 //#include <format> This isn't supported in gcc yet, although I wish it were because this would be a cool way to interpolate strings
#ifdef _WIN32
#include <format>
#else
#include <sstream>
#endif
#include <cstdint>

///////////////////////////////////////////////////////////////////////////////
//
// GLOBAL VARIABLES
//
///////////////////////////////////////////////////////////////////////////////
typedef uint16_t ui16;
typedef std::tuple<ui16, ui16, ui16> console_color_t;
typedef std::tuple<ui16, ui16> console_cursor_pos_t;

const console_color_t CONSOLE_COLOR_WHITE = std::make_tuple<ui16, ui16, ui16>(255, 255, 255);
const console_color_t CONSOLE_COLOR_RED = std::make_tuple<ui16, ui16, ui16>(255, 0, 0);
const console_color_t CONSOLE_COLOR_GREEN = std::make_tuple<ui16, ui16, ui16>(0, 255, 0);
const console_color_t CONSOLE_COLOR_BLUE = std::make_tuple<ui16, ui16, ui16>(0, 0, 255);
const console_color_t CONSOLE_COLOR_GOLD = std::make_tuple<ui16, ui16, ui16>(255, 215, 0);
const console_color_t CONSOLE_COLOR_ROYALBLUE = std::make_tuple<ui16, ui16, ui16>(65, 105, 255);
const console_color_t CONSOLE_COLOR_DODGERBLUE = std::make_tuple<ui16, ui16, ui16>(30, 144, 255);
const console_color_t CONSOLE_COLOR_MINTGREEN = std::make_tuple<ui16, ui16, ui16>(152, 255, 152);
const console_color_t CONSOLE_COLOR_PUMPKIN = std::make_tuple<ui16, ui16, ui16>(255, 117, 24);
const console_color_t CONSOLE_COLOR_BLACK = std::make_tuple<ui16, ui16, ui16>(0, 0, 0);
const console_color_t CONSOLE_COLOR_COBALT = std::make_tuple<ui16, ui16, ui16>(0, 71, 171);
const console_color_t CONSOLE_COLOR_LEMON_GLACIER = std::make_tuple<ui16, ui16, ui16>(253, 255, 0);


///////////////////////////////////////////////////////////////////////////////
//
// PLAYER VARIABLES
//
///////////////////////////////////////////////////////////////////////////////
std::string player_name = "Steve";
ui16 player_current_hp = 100;
ui16 player_maximum_hp = 100;
ui16 player_current_mp = 50;
ui16 player_maximum_mp = 50;
ui16 player_current_gold = 5000;
ui16 player_maximum_gold = 5000;
const console_color_t PLAYER_STAT_DRAW_NAME_COLOR = CONSOLE_COLOR_DODGERBLUE;
const console_color_t PLAYER_STAT_DRAW_NUM_SAFE = CONSOLE_COLOR_GREEN;
const console_color_t PLAYER_STAT_DRAW_NUM_CAUTION = CONSOLE_COLOR_PUMPKIN;
const console_color_t PLAYER_STAT_DRAW_NUM_DANGER = CONSOLE_COLOR_RED;
const console_color_t PLAYER_STAT_DRAW_GOLD_COLOR = CONSOLE_COLOR_GOLD;


///////////////////////////////////////////////////////////////////////////////
//
// GLOBAL SCREEN SETTINGS
//
///////////////////////////////////////////////////////////////////////////////
const ui16 SCREEN_ORIGIN_X = 1;
const ui16 SCREEN_ORIGIN_Y = 1;
const ui16 SCREEN_ROWS = 25 + SCREEN_ORIGIN_Y; // Accounts for the 1-index
const ui16 SCREEN_COLS = 80 + SCREEN_ORIGIN_X; // Accounts for the 1-index
const console_cursor_pos_t SCREEN_ORIGIN_POS = std::make_tuple<ui16, ui16>((SCREEN_ORIGIN_X + 0), (SCREEN_ORIGIN_Y + 0));


///////////////////////////////////////////////////////////////////////////////
//
// UI STATUS WINDOW VARIABLES
//
// Note that for the variables whose assignments are std::make_tuple,
// the pattern of passing a parens const + 0 literal is to circumvent the rvalue
// constraint on these parameters as they're required by the STL. This pattern
// is employed further down in the code, notable in window drawing functions
// so that the vertical borders can be drawn inside classic loops using the
// loop's probe.
//
///////////////////////////////////////////////////////////////////////////////
const console_color_t UI_STATUSWINDOW_BORDER_COLOR = CONSOLE_COLOR_WHITE;
const std::string UI_STATUSWINDOW_BORDER_HORIZONTAL = "@--~---~---~---~---@";
const std::string UI_STATUSWINDOW_BORDER_VERTICAL = "|";
const ui16 UI_STATUSWINDOW_TOP = SCREEN_ORIGIN_Y;
const ui16 UI_STATUSWINDOW_LEFT = SCREEN_ORIGIN_X;
//const ui16 UI_STATUSWINDOW_WIDTH = 20;
const ui16 UI_STATUSWINDOW_WIDTH = UI_STATUSWINDOW_LEFT + 19;
//const ui16 UI_STATUSWINDOW_HEIGHT = 11;
const ui16 UI_STATUSWINDOW_HEIGHT = UI_STATUSWINDOW_TOP + 10;
//const ui16 UI_STATUSWINDOW_PLAYERNAME_DRAW_ROW = 3;
const ui16 UI_STATUSWINDOW_PLAYERNAME_DRAW_ROW = UI_STATUSWINDOW_TOP + 2;
//const ui16 UI_STATUSWINDOW_PLAYERNAME_DRAW_COL = 3;
const ui16 UI_STATUSWINDOW_PLAYERNAME_DRAW_COL = UI_STATUSWINDOW_LEFT + 2;
//const ui16 UI_STATUSWINDOW_PLAYERHP_DRAW_ROW = 5;
const ui16 UI_STATUSWINDOW_PLAYERHP_DRAW_ROW = UI_STATUSWINDOW_PLAYERNAME_DRAW_ROW + 2;
//const ui16 UI_STATUSWINDOW_PLAYERHP_DRAW_COL = 3;
const ui16 UI_STATUSWINDOW_PLAYERHP_DRAW_COL = UI_STATUSWINDOW_LEFT + 2;
//const ui16 UI_STATUSWINDOW_PLAYERMP_DRAW_ROW = 7;
const ui16 UI_STATUSWINDOW_PLAYERMP_DRAW_ROW = UI_STATUSWINDOW_PLAYERHP_DRAW_ROW + 2;
//const ui16 UI_STATUSWINDOW_PLAYERMP_DRAW_COL = 3;
const ui16 UI_STATUSWINDOW_PLAYERMP_DRAW_COL = UI_STATUSWINDOW_LEFT + 2;
//const ui16 UI_STATUSWINDOW_PLAYERG_DRAW_ROW = 9;
const ui16 UI_STATUSWINDOW_PLAYERG_DRAW_ROW = UI_STATUSWINDOW_PLAYERMP_DRAW_ROW + 2;
//const ui16 UI_STATUSWINDOW_PLAYERG_DRAW_COL = 3;
const ui16 UI_STATUSWINDOW_PLAYERG_DRAW_COL = UI_STATUSWINDOW_LEFT + 2;
const console_cursor_pos_t UI_STATUSWINDOW_TOPLEFT = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_TOP + 0), (UI_STATUSWINDOW_LEFT + 0));
const console_cursor_pos_t UI_STATUSWINDOW_BOTTOMRIGHT = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_HEIGHT + 0), (UI_STATUSWINDOW_WIDTH + 0));
const console_cursor_pos_t UI_STATUSWINDOW_HORIZTOP_POS = UI_STATUSWINDOW_TOPLEFT;
const console_cursor_pos_t UI_STATUSWINDOW_HORIZBOT_POS = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_HEIGHT + 0), (UI_STATUSWINDOW_LEFT + 0));
const console_cursor_pos_t UI_STATUSWINDOW_PLAYERNAME_DRAW_POS = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_PLAYERNAME_DRAW_ROW + 0), (UI_STATUSWINDOW_PLAYERNAME_DRAW_COL + 0));
const console_cursor_pos_t UI_STATUSWINDOW_PLAYERHP_DRAW_POS = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_PLAYERHP_DRAW_ROW + 0), (UI_STATUSWINDOW_PLAYERHP_DRAW_COL + 0));
const console_cursor_pos_t UI_STATUSWINDOW_PLAYERMP_DRAW_POS = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_PLAYERMP_DRAW_ROW + 0), (UI_STATUSWINDOW_PLAYERMP_DRAW_COL + 0));
const console_cursor_pos_t UI_STATUSWINDOW_PLAYERG_DRAW_POS = std::make_tuple<ui16, ui16>((UI_STATUSWINDOW_PLAYERG_DRAW_ROW + 0), (UI_STATUSWINDOW_PLAYERG_DRAW_COL + 0));

///////////////////////////////////////////////////////////////////////////////
//
// UI COMMAND WINDOW VARIABLES 
//
///////////////////////////////////////////////////////////////////////////////
struct ui_cmdwin_hist_msg_t {
    std::string message;
    console_color_t foreground_color;
};

const console_color_t UI_COMMANDWINDOW_BORDER_COLOR = CONSOLE_COLOR_WHITE;
const console_color_t UI_COMMANDWINDOW_HIST_VALID_COLOR = CONSOLE_COLOR_MINTGREEN;
const console_color_t UI_COMMANDWINDOW_HIST_INVALID_COLOR = CONSOLE_COLOR_RED;
const console_color_t UI_COMMANDWINDOW_BLANK_COLOR = CONSOLE_COLOR_BLACK;
const console_color_t UI_COMMANDWINDOW_CMDDIV_COLOR = CONSOLE_COLOR_COBALT;
const std::string UI_COMMANDWINDOW_BORDER_HORIZONTAL = "@--~---~---~---~---@";
const std::string UI_COMMANDWINDOW_BORDER_VERTICAL = "|";
//const std::string UI_COMMANDWINDOW_BORDER_CMDDIV = "``````````````````";
const std::string UI_COMMANDWINDOW_BORDER_CMDDIV = "==================";
const std::string UI_COMMANDWINDOW_CMD_ACTUAL = "";
const std::string UI_COMMANDWINDOW_CMD_BLANK = "                  ";
ui_cmdwin_hist_msg_t ui_commandwindow_hist_a = { "", UI_COMMANDWINDOW_HIST_VALID_COLOR };
ui_cmdwin_hist_msg_t ui_commandwindow_hist_b = { "", UI_COMMANDWINDOW_HIST_VALID_COLOR };
ui_cmdwin_hist_msg_t ui_commandwindow_hist_c = { "", UI_COMMANDWINDOW_HIST_VALID_COLOR };
ui_cmdwin_hist_msg_t ui_commandwindow_hist_d = { "", UI_COMMANDWINDOW_HIST_VALID_COLOR };
const ui16 UI_COMMANDWINDOW_TOP = (UI_STATUSWINDOW_TOP + UI_STATUSWINDOW_HEIGHT);
//const ui16 UI_COMMANDWINDOW_LEFT = 1;
const ui16 UI_COMMANDWINDOW_LEFT = SCREEN_ORIGIN_X;
//const ui16 UI_COMMANDWINDOW_WIDTH = 20;
const ui16 UI_COMMANDWINDOW_WIDTH = UI_COMMANDWINDOW_LEFT + 19;
//const ui16 UI_COMMANDWINDOW_HEIGHT = 7;
const ui16 UI_COMMANDWINDOW_HEIGHT = UI_COMMANDWINDOW_TOP + 6;
//const ui16 UI_COMMANDWINDOW_CMDDIV_TOP = (UI_COMMANDWINDOW_TOP + UI_COMMANDWINDOW_HEIGHT) - 2;
const ui16 UI_COMMANDWINDOW_CMDDIV_TOP = UI_COMMANDWINDOW_HEIGHT - 2;
const ui16 UI_COMMANDWINDOW_CMDDIV_LEFT = UI_COMMANDWINDOW_LEFT + 1;
const ui16 UI_COMMANDWINDOW_HIST_LEFT = UI_COMMANDWINDOW_LEFT + 1;
//const ui16 UI_COMMANDWINDOW_HISTD_TOP = (UI_COMMANDWINDOW_TOP + UI_COMMANDWINDOW_HEIGHT) - 3;
const ui16 UI_COMMANDWINDOW_HISTD_TOP = UI_COMMANDWINDOW_HEIGHT - 3;
//const ui16 UI_COMMANDWINDOW_HISTC_TOP = (UI_COMMANDWINDOW_TOP + UI_COMMANDWINDOW_HEIGHT) - 4;
const ui16 UI_COMMANDWINDOW_HISTC_TOP = UI_COMMANDWINDOW_HEIGHT - 4;
//const ui16 UI_COMMANDWINDOW_HISTB_TOP = (UI_COMMANDWINDOW_TOP + UI_COMMANDWINDOW_HEIGHT) - 5;
const ui16 UI_COMMANDWINDOW_HISTB_TOP = UI_COMMANDWINDOW_HEIGHT - 5;
//const ui16 UI_COMMANDWINDOW_HISTA_TOP = (UI_COMMANDWINDOW_TOP + UI_COMMANDWINDOW_HEIGHT) - 6;
const ui16 UI_COMMANDWINDOW_HISTA_TOP = UI_COMMANDWINDOW_HEIGHT - 6;
const console_cursor_pos_t UI_COMMANDWINDOW_TOPLEFT = std::make_tuple<ui16, ui16>((UI_COMMANDWINDOW_TOP + 0), (UI_COMMANDWINDOW_LEFT + 0));
const console_cursor_pos_t UI_COMMANDWINDOW_BOTTOMRIGHT = std::make_tuple<ui16, ui16>((UI_COMMANDWINDOW_HEIGHT + 0), (UI_COMMANDWINDOW_WIDTH + 0));
const console_cursor_pos_t UI_COMMANDWINDOW_HORIZTOP_POS = UI_COMMANDWINDOW_TOPLEFT;
//const console_cursor_pos_t UI_COMMANDWINDOW_HORIZBOT_POS = std::make_tuple<ui16, ui16>(((UI_COMMANDWINDOW_TOP + UI_COMMANDWINDOW_HEIGHT) + 0), (UI_COMMANDWINDOW_LEFT + 0));
const console_cursor_pos_t UI_COMMANDWINDOW_HORIZBOT_POS = std::make_tuple<ui16, ui16>((UI_COMMANDWINDOW_HEIGHT + 0), (UI_COMMANDWINDOW_LEFT + 0));
const console_cursor_pos_t UI_COMMANDWINDOW_CMDDIV_POS = std::make_tuple<ui16, ui16>((UI_COMMANDWINDOW_CMDDIV_TOP + 0), (UI_COMMANDWINDOW_CMDDIV_LEFT + 0));


///////////////////////////////////////////////////////////////////////////////
//
// UI MESSAGE WINDOW VARIABLES 
//
///////////////////////////////////////////////////////////////////////////////
struct ui_msgwin_hist_msg_t {
    std::string msg;
    console_color_t fgc;
};

const console_color_t UI_MESSAGEWINDOW_BORDER_COLOR = CONSOLE_COLOR_WHITE;
const console_color_t UI_MESSAGEWINDOW_BLANK_COLOR = CONSOLE_COLOR_BLACK;
const std::string UI_MESSAGEWINDOW_BORDER_HORIZONTAL = "@------------------------------------------------------------------------------@";
const std::string UI_MESSAGEWINDOW_BORDER_VERTICAL = "|";
const std::string UI_MESSAGEWINDOW_BLANK = "                                                                                ";
ui_msgwin_hist_msg_t ui_messagewindow_hist_a = { "", CONSOLE_COLOR_WHITE };
ui_msgwin_hist_msg_t ui_messagewindow_hist_b = { "", CONSOLE_COLOR_WHITE };
ui_msgwin_hist_msg_t ui_messagewindow_hist_c = { "", CONSOLE_COLOR_WHITE };
const ui16 UI_MESSAGEWINDOW_TOP = UI_COMMANDWINDOW_HEIGHT + 1;
const ui16 UI_MESSAGEWINDOW_LEFT = SCREEN_ORIGIN_X;
const ui16 UI_MESSAGEWINDOW_WIDTH = SCREEN_COLS;
const ui16 UI_MESSAGEWINDOW_HEIGHT = UI_MESSAGEWINDOW_TOP + 6;
const ui16 UI_MESSAGEWINDOW_HIST_LEFT = UI_MESSAGEWINDOW_LEFT + 1;
//const ui16 UI_MESSAGEWINDOW_HISTC_TOP = (UI_MESSAGEWINDOW_TOP + UI_MESSAGEWINDOW_HEIGHT) - 1;
const ui16 UI_MESSAGEWINDOW_HISTC_TOP = UI_MESSAGEWINDOW_HEIGHT - 1;
//const ui16 UI_MESSAGEWINDOW_HISTB_TOP = (UI_MESSAGEWINDOW_TOP + UI_MESSAGEWINDOW_HEIGHT) - 2;
const ui16 UI_MESSAGEWINDOW_HISTB_TOP = UI_MESSAGEWINDOW_HEIGHT - 2;
//const ui16 UI_MESSAGEWINDOW_HISTA_TOP = (UI_MESSAGEWINDOW_TOP + UI_MESSAGEWINDOW_HEIGHT) - 3;
const ui16 UI_MESSAGEWINDOW_HISTA_TOP = UI_MESSAGEWINDOW_HEIGHT - 3;
const console_cursor_pos_t UI_MESSAGEWINDOW_TOPLEFT = std::make_tuple<ui16, ui16>((UI_MESSAGEWINDOW_TOP + 0), (UI_MESSAGEWINDOW_LEFT + 0));
const console_cursor_pos_t UI_MESSAGEWINDOW_BOTTOMRIGHT = std::make_tuple<ui16, ui16>((UI_MESSAGEWINDOW_HEIGHT + 0), (UI_MESSAGEWINDOW_WIDTH + 0));
const console_cursor_pos_t UI_MESSAGEWINDOW_HORIZTOP_POS = UI_MESSAGEWINDOW_TOPLEFT;
const console_cursor_pos_t UI_MESSAGEWINDOW_HORIZBOT_POS = std::make_tuple<ui16, ui16>((UI_MESSAGEWINDOW_HEIGHT + 0), (UI_MESSAGEWINDOW_LEFT + 0));







///////////////////////////////////////////////////////////////////////////////
//
// GLOBAL FUNCTION DEFINITIONS
//
///////////////////////////////////////////////////////////////////////////////
const std::string gen_console_color_str(const console_color_t& fg, const console_color_t& bg, const std::string& str) {
#ifdef _WIN32
    return std::format("\033[38;2;{};{};{}m\033[48;2;{};{};{}m{}\033[m",
        std::to_string(std::get<0>(fg)),
        std::to_string(std::get<1>(fg)),
        std::to_string(std::get<2>(fg)),
        std::to_string(std::get<0>(bg)),
        std::to_string(std::get<1>(bg)),
        std::to_string(std::get<2>(bg)),
        str);
#else
    std::stringstream ss;
    ss << "\033[38;2;" << std::get<0>(fg) << ";" << std::get<1>(fg) << ";" << std::get<2>(fg) << "m\033[48;2;" << std::get<0>(bg) << ";" << std::get<1>(bg) << ";" << std::get<2>(bg) << "m" << str << "\033[m";

    return ss.str();
#endif
}

const std::string gen_console_cursorpos_str(const console_cursor_pos_t& pos) {
#ifdef _WIN32
    return std::format("\033[{};{}H",
        std::get<0>(pos),
        std::get<1>(pos));
#else
    std::stringstream ss;
    ss << "\033[" << std::get<0>(pos) << ";" << std::get<1>(pos) << "H";

    return ss.str();
#endif
}

void screen_clear_play_area() {
#ifdef _WIN32
    for (ui16 a = SCREEN_ORIGIN_Y; a < SCREEN_ROWS; a++) {
        for (ui16 b = SCREEN_ORIGIN_X; b < SCREEN_COLS; b++) {
            std::cout << std::format("{}{}",
                gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (b + 0))),
                gen_console_color_str(CONSOLE_COLOR_BLACK, CONSOLE_COLOR_BLACK, " "));
        }
    }
#else
    std::stringstream ss;

    for (ui16 a = SCREEN_ORIGIN_Y; a < SCREEN_ROWS; a++) {
        for (ui16 b = SCREEN_ORIGIN_X; b < SCREEN_COLS; b++) {
            ss << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (b + 0)))
                << gen_console_color_str(CONSOLE_COLOR_BLACK, CONSOLE_COLOR_BLACK, " ");
        }
    }

    std::cout << ss.str();
#endif
}

const std::string format_player_name() {
#ifdef _WIN32
    return std::format("{}", gen_console_color_str(PLAYER_STAT_DRAW_NAME_COLOR, CONSOLE_COLOR_BLACK, player_name));
#else
    std::stringstream ss;
    ss << gen_console_color_str(PLAYER_STAT_DRAW_NAME_COLOR, CONSOLE_COLOR_BLACK, player_name);

    return ss.str();
#endif
}

const std::string format_player_hp() {
#ifdef _WIN32
    return std::format("{}{}\n\t{}",
        gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "H "),
        gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, std::to_string(player_current_hp)),
        gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "/ " + std::to_string(player_maximum_hp)));
#else
    std::stringstream ss;
    ss << gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "H ")
        << gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, std::to_string(player_current_hp))
        << "\n\t"
        << gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "/ " + std::to_string(player_maximum_hp));

    return ss.str();
#endif
}

const std::string format_player_mp() {
#ifdef _WIN32
    return std::format("{}{}\n\t{}", 
        gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "M "),
        gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, std::to_string(player_current_mp)),
        gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "/ " + std::to_string(player_maximum_mp)));
#else
    std::stringstream ss;
    ss << gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "M ")
        << gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, std::to_string(player_current_mp))
        << "\n\t"
        << gen_console_color_str(PLAYER_STAT_DRAW_NUM_SAFE, CONSOLE_COLOR_BLACK, "/ " + std::to_string(player_maximum_mp));

    return ss.str();
#endif
}

const std::string format_player_gold() {
#ifdef _WIN32
    return std::format("{}", gen_console_color_str(PLAYER_STAT_DRAW_GOLD_COLOR, CONSOLE_COLOR_BLACK, "G" + std::to_string(player_current_gold)));
#else
    std::stringstream ss;
    ss << gen_console_color_str(PLAYER_STAT_DRAW_GOLD_COLOR, CONSOLE_COLOR_BLACK, "G" + std::to_string(player_current_gold));

    return ss.str();
#endif
}

void ui_statuswindow_draw() {
#ifdef _WIN32
    std::string horizontal_borders = std::format("{}{}{}{}",
        gen_console_cursorpos_str(UI_STATUSWINDOW_HORIZTOP_POS),
        gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_HORIZONTAL),
        gen_console_cursorpos_str(UI_STATUSWINDOW_HORIZBOT_POS),
        gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_HORIZONTAL));
    std::string vertical_left_border, vertical_right_border;
    
    for (ui16 a = 2; a < UI_STATUSWINDOW_HEIGHT; a++) {
        vertical_left_border += std::format("{}{}",
            gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_STATUSWINDOW_LEFT + 0))),
            gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_VERTICAL));
        vertical_right_border += std::format("{}{}",
            gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_STATUSWINDOW_WIDTH + 0))),
            gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_VERTICAL));
    }

    std::cout << horizontal_borders << vertical_left_border << vertical_right_border;
#else
    std::stringstream horizontal_borders;
    std::stringstream vertical_left_border, vertical_right_border;

    horizontal_borders << gen_console_cursorpos_str(UI_STATUSWINDOW_HORIZTOP_POS)
        << gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_HORIZONTAL)
        << gen_console_cursorpos_str(UI_STATUSWINDOW_HORIZBOT_POS)
        << gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_HORIZONTAL);

    for (ui16 a = 2; a < UI_STATUSWINDOW_HEIGHT; a++) {
        vertical_left_border << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_STATUSWINDOW_LEFT + 0)))
            << gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_VERTICAL);
        vertical_right_border << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_STATUSWINDOW_WIDTH + 0)))
            << gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_VERTICAL);
    }

    std::cout << horizontal_borders.str() << vertical_left_border.str() << vertical_right_border.str();
#endif
}

void ui_statuswindow_update_data() {
#ifdef _WIN32
    std::cout << std::format("{}{}{}{}{}{}{}{}",
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERNAME_DRAW_POS),
        format_player_name(),
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERHP_DRAW_POS),
        format_player_hp(),
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERMP_DRAW_POS),
        format_player_mp(),
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERG_DRAW_POS),
        format_player_gold());
#else
    std::stringstream data;

    data << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERNAME_DRAW_POS)
        << format_player_name()
        << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERHP_DRAW_POS)
        << format_player_hp()
        << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERMP_DRAW_POS)
        << format_player_mp()
        << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERG_DRAW_POS)
        << format_player_gold();

    std::cout << data.str();
#endif
}

void ui_statuswindow_update_player_name() {
#ifdef _WIN32
    std::cout << std::format("{}{}",
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERNAME_DRAW_POS),
        format_player_name());
#else
    std::stringstream ss;

    ss << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERNAME_DRAW_POS)
        << format_player_name();

    std::cout << ss.str();
#endif
}

void ui_statuswindow_update_player_hp() {
#ifdef _WIN32
    std::cout << std::format("{}{}",
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERHP_DRAW_POS),
        format_player_hp());
#else
    std::stringstream ss;

    ss << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERHP_DRAW_POS)
        << format_player_hp();

    std::cout << ss.str();
#endif
}

void ui_statuswindow_update_player_mp() {
#ifdef _WIN32
    std::cout << std::format("{}{}",
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERMP_DRAW_POS),
        format_player_mp());
#else
    std::stringstream ss;

    ss << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERMP_DRAW_POS)
        << format_player_mp();

    std::cout << ss.str();
#endif
}

void ui_statuswindow_update_player_gold() {
#ifdef _WIN32
    std::cout << std::format("{}{}",
        gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERG_DRAW_POS),
        format_player_gold());
#else
    std::stringstream ss;

    ss << gen_console_cursorpos_str(UI_STATUSWINDOW_PLAYERG_DRAW_POS)
        << format_player_gold();

    std::cout << ss.str();
#endif
}

void ui_commandwindow_draw() {
#ifdef _WIN32
    std::string horizontal_borders = std::format("{}{}{}{}",
        gen_console_cursorpos_str(UI_COMMANDWINDOW_HORIZTOP_POS),
        gen_console_color_str(UI_COMMANDWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_HORIZONTAL),
        gen_console_cursorpos_str(UI_COMMANDWINDOW_HORIZBOT_POS),
        gen_console_color_str(UI_COMMANDWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_HORIZONTAL));
    std::string cmddiv_border = std::format("{}{}",
        gen_console_cursorpos_str(UI_COMMANDWINDOW_CMDDIV_POS),
        gen_console_color_str(UI_COMMANDWINDOW_CMDDIV_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_CMDDIV));
    std::string vertical_left_border, vertical_right_border;

    for (ui16 a = (UI_COMMANDWINDOW_TOP + 1); a < UI_COMMANDWINDOW_HEIGHT; a++) {
        vertical_left_border += std::format("{}{}",
            gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_COMMANDWINDOW_LEFT + 0))),
            gen_console_color_str(UI_COMMANDWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_VERTICAL));
        vertical_right_border += std::format("{}{}",
            gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_COMMANDWINDOW_WIDTH + 0))),
            gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_VERTICAL));
    }

    std::cout << horizontal_borders << cmddiv_border << vertical_left_border << vertical_right_border;
#else
    std::stringstream horizontal_borders, vertical_left_border, vertical_right_border, cmddiv_border;

    horizontal_borders << gen_console_cursorpos_str(UI_COMMANDWINDOW_HORIZTOP_POS)
        << gen_console_color_str(UI_COMMANDWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_HORIZONTAL)
        << gen_console_cursorpos_str(UI_COMMANDWINDOW_HORIZBOT_POS)
        << gen_console_color_str(UI_COMMANDWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_HORIZONTAL);
    cmddiv_border << gen_console_cursorpos_str(UI_COMMANDWINDOW_CMDDIV_POS)
        << gen_console_color_str(UI_COMMANDWINDOW_CMDDIV_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_CMDDIV);
    for (ui16 a = (UI_COMMANDWINDOW_TOP + 1); a < UI_COMMANDWINDOW_HEIGHT; a++) {
        vertical_left_border << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_COMMANDWINDOW_LEFT + 0)))
            << gen_console_color_str(UI_COMMANDWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_COMMANDWINDOW_BORDER_VERTICAL);
        vertical_right_border << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_COMMANDWINDOW_WIDTH + 0)))
            << gen_console_color_str(UI_STATUSWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_STATUSWINDOW_BORDER_VERTICAL);
    }

    std::cout << horizontal_borders.str() << cmddiv_border.str() << vertical_left_border.str() << vertical_right_border.str();
#endif
}

void ui_messagewindow_draw() {
#ifdef _WIN32
    std::string horizontal_borders = std::format("{}{}{}{}",
        gen_console_cursorpos_str(UI_MESSAGEWINDOW_HORIZTOP_POS),
        gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_HORIZONTAL),
        gen_console_cursorpos_str(UI_MESSAGEWINDOW_HORIZBOT_POS),
        gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_HORIZONTAL));
    std::string vertical_left_border, vertical_right_border;

    for (ui16 a = (UI_MESSAGEWINDOW_TOP + 1); a < UI_MESSAGEWINDOW_HEIGHT; a++) {
        vertical_left_border += std::format("{}{}",
            gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_MESSAGEWINDOW_LEFT + 0))),
            gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_VERTICAL));
        vertical_right_border += std::format("{}{}",
            gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_MESSAGEWINDOW_WIDTH + 0) - 1)),
            gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_VERTICAL));
    }

    std::cout << horizontal_borders << vertical_left_border << vertical_right_border;
#else
    std::stringstream horizontal_borders, vertical_left_border, vertical_right_border;

    horizontal_borders << gen_console_cursorpos_str(UI_MESSAGEWINDOW_HORIZTOP_POS)
        << gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_HORIZONTAL)
        << gen_console_cursorpos_str(UI_MESSAGEWINDOW_HORIZBOT_POS)
        << gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_HORIZONTAL);
    for (ui16 a = (UI_MESSAGEWINDOW_TOP + 1); a < UI_MESSAGEWINDOW_HEIGHT; a++) {
        vertical_left_border << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_MESSAGEWINDOW_LEFT + 0)))
            << gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_VERTICAL);
        vertical_right_border << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((a + 0), (UI_MESSAGEWINDOW_WIDTH + 0) - 1))
            << gen_console_color_str(UI_MESSAGEWINDOW_BORDER_COLOR, CONSOLE_COLOR_BLACK, UI_MESSAGEWINDOW_BORDER_VERTICAL);
    }

    std::cout << horizontal_borders.str() << vertical_left_border.str() << vertical_right_border.str();
#endif
}

int main(int argc, char** argv) {
    // Attempt to clear the screen using the CSI
    std::cout << "\033[2J";

    screen_clear_play_area();

    //std::cout 
    //    << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>((SCREEN_ORIGIN_Y + 0), (SCREEN_ORIGIN_X + 0)))
    //    << gen_console_color_str(CONSOLE_COLOR_PUMPKIN, CONSOLE_COLOR_BLACK, "Hello, world!");

    ui_statuswindow_draw();
    ui_statuswindow_update_data();

    ui_commandwindow_draw();

    ui_messagewindow_draw();

    //std::cout << getenv("COLORTERM") << std::endl;

    std::cout << gen_console_cursorpos_str(std::make_tuple<ui16, ui16>(30, 0));

    while (1);

    return 0;
}

