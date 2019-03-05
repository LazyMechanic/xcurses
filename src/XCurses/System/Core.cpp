#include <XCurses/System/Core.h>

#include <algorithm>

#include <PDCurses/curses.h>

#include <XCurses/System/Input.h>
#include <XCurses/Graphics/Context.h>

namespace xcur {
Core::Core()
{
    initscr();
}

Core::~Core()
{
    endwin();
}

void Core::init(const CoreConfig& config)
{
    this->setCBreakMode(config.enableCBreakMode);
    this->setEchoMode(config.enableEchoMode);
    this->setRawMode(config.enableRawMode);
    this->setNewLineMode(config.enableNewLineMode);
    this->setTerminalSize(config.terminalSize);

}

Status Core::setCBreakMode(bool v)
{
    m_config.enableCBreakMode = v;
    if (v) {
        return cbreak();
    }
    else {
        return nocbreak();
    }
}

bool Core::isCBreakMode() const
{
	return m_config.enableCBreakMode;
}

Status Core::setEchoMode(bool v)
{
    m_config.enableEchoMode = v;
    if (v) {
        return echo();
    }
    else {
        return noecho();
    }
}

bool Core::isEchoMode() const
{
	return m_config.enableEchoMode;
}

Status Core::setRawMode(bool v)
{
    m_config.enableRawMode = v;
    if (v) {
        return raw();
    }
    else {
        return noraw();
    }
}

bool Core::isRawMode() const
{
	return m_config.enableRawMode;
}

Status Core::setNewLineMode(bool v)
{
    m_config.enableNewLineMode = v;
    if (v) {
        return nl();
    }
    else {
        return nonl();
    }
}

bool Core::isNewLineMode() const
{
	return m_config.enableNewLineMode;
}

Status Core::setTerminalSize(const Vector2u& size)
{
	Status result = resize_term(size.y, size.x);
    m_config.terminalSize = Vector2u(getmaxx(stdscr), getmaxy(stdscr));
    return result;
}

Vector2u Core::getTerminalSize() const
{
	return m_config.terminalSize;
}

Status Core::blinkColors() const
{
    return flash();
}

Status Core::playBeepSound() const
{
    return beep();
}

bool Core::isTerminalResized() const
{
	return m_isTermResized;
}

void Core::handleEvents()
{
    // TODO: call current context handleEvents() func
}

void Core::update(const float dt)
{
    // TODO: call current context update() func

	m_isTermResized = false;
}

void Core::draw()
{
    /*
        // Clear virtual screen
        clear();
        wnoutrefresh(stdscr);
        // Draw all windows
        for (auto& window : m_windows) {
            window->draw();
        }
        // Draw all windows
        doupdate();
    */
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ all work code, copy to context
    // TODO: call current context draw() func
}
}