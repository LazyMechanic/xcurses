#pragma once

#include <XCurses/System/Vector2.h>
#include <XCurses/Graphics/Widget.h>
#include <XCurses/System/CursorState.h>

namespace xcur {
/**
 * \brief Inherit this class if you need widget with input field
 */
class Inputtable : public Widget
{
public:
    /**
     * \brief Predefined nullptr Inputtable
     */
    static const Object::Ptr<Inputtable> None;

    /**
     * \brief Create Inputtable
     * \return Smart ptr to Inputtable
     */
    static Object::Ptr<Inputtable> create();

    /**
     * \brief Inputtable destructor.
     */
    virtual ~Inputtable() = default;

    /**
     * \brief Set cursor position. 
     * Position coordinates that exceed widget size are clamped to widget size.
     * \param newPosition New cursor position
     */
    void setCursorPosition(const Vector2u& newPosition);

    /**
     * \brief Get current cursor position
     * \return Coordinate
     */
    Vector2u getCursorPosition() const;

    /**
     * \brief Set new cursor state
     * \param newState Cursor state
     */
    void setCursorState(CursorState newState);

    /**
     * \brief Get cursor state
     * \return Cursor state
     */
    CursorState getCursorState() const;

    /**
     * \brief Set widget size
     * \param size New size
     */
    void setSize(const Vector2u& size);

    /**
     * \brief Get widget size
     * \return Size
     */
    Vector2u getSize() const;

protected:
    /**
     * \brief Default Inputtable constructor.
     */
    Inputtable();

    /**
     * \brief Widget size
     */
    Vector2u m_size;

    /**
     * \brief Current cursor position
     */
    Vector2u m_cursorPosition;

    /**
     * \brief Cursor state
     */
    CursorState m_cursorState;
};
}