#pragma once

#include <cstdint>

namespace xcur {
/**
 * \brief This class stores color with component between 0 and 255.
 * Curses color standard defines that the color component must be
 * between 0 and 1000.
 */
class Color
{
public:
    /**
     * \brief Default Color constructor. Creates Color(0, 0, 0) that means black
     * color
     */
    Color();

    /**
     * \brief Constructor the color from its 3 RGB components
     * \param red Red component (in the range [0, 255])
     * \param green Green component (in the range [0, 255])
     * \param blue Blue component (in the range [0, 255])
     */
    Color(uint8_t red, uint8_t green, uint8_t blue);

    /**
     * \brief Contruct the color from 32-bit unsigned integer
     * \param color Number containing the RGB components (in that order).
     * Format is 0x00ffffff
     */
    explicit Color(uint32_t color);

    /**
     * \brief Copy Color constructor
     */
    Color(const Color&) = default;

    /**
     * \brief Move Color constructor
     */
    Color(Color&&) = default;

    /**
     * \brief Default copy assignment operator
     * \return Reference to \a this
     */
    Color& operator =(const Color&) = default;

    /**
     * \brief Default move assignment operator
     * \return Reference to \a this
     */
    Color& operator =(Color&&) = default;

    /**
     * \brief Overload of the == operator
     * This operator compares two colors and check if they are equal.
     * \param right Right operand
     * \return True if colors are equal, false if they are different
     */
    bool operator ==(const Color& right) const;

    /**
     * \brief Overload of the != operator
     * This operator compares two colors and check if they are different.
     * \param right Right operand
     * \return True if colors are different, false if they are equal
     */
    bool operator !=(const Color& right) const;

    /**
     * \brief Overload of the binary + operator
     * This operator returns the component-wise sum of two colors.
     * Components that exceed 255 are clamped to 255.
     * \param right Right operand
     * \return Result of \a left + \a right
     */
    Color operator +(const Color& right) const;

    /**
     * \brief Overload of the binary - operator
     * This operator returns the component-wise subtraction of two colors.
     * Components below 0 are clamped to 0.
     * \param right Right operand
     * \return Result of \a left - \a right
     */
    Color operator -(const Color& right) const;

    /**
     * \brief Overload of the binary * operator
     * This operator returns the component-wise multiplication
     * (also called "modulation") of two colors.
     * Components are then divided by 255 so that the result is
     * still in the range [0, 255].
     * \param right Right operand
     * \return Result of \a left * \a right
     */
    Color operator *(const Color& right) const;

    /**
     * \brief Overload of the binary += operator
     * This operator computes the component-wise sum of two colors,
     * and assigns the result to the left operand.
     * Components that exceed 255 are clamped to 255.
     * \param right Right operand
     * \return Reference to \a left
     */
    Color& operator +=(const Color& right);

    /**
     * \brief Overload of the binary -= operator
     * This operator computes the component-wise subtraction of two colors,
     * and assigns the result to the left operand.
     * Components below 0 are clamped to 0.
     * \param right Right operand
     * \return Reference to \a left
     */
    Color& operator -=(const Color& right);

    /**
     * \brief Overload of the binary *= operator
     * This operator returns the component-wise multiplication
     * (also called "modulation") of two colors, and assigns
     * the result to the left operand.
     * Components are then divided by 255 so that the result is
     * still in the range [0, 255].
     * \param right Right operand
     * \return Reference to \a left
     */
    Color& operator *=(const Color& right);

    /**
     * \brief Color destructor
     */
    ~Color() = default;

    /**
     * \brief Black predefined color
     */
    static const Color Black;

    /**
     * \brief Red predefined color
     */
    static const Color Red;

    /**
     * \brief Green predefined color
     */
    static const Color Green;

    /**
     * \brief Blue predefined color
     */
    static const Color Blue;

    /**
     * \brief Yellow predefined color
     */
    static const Color Yellow;

    /**
     * \brief Magenta predefined color
     */
    static const Color Magenta;

    /**
     * \brief Cyan predefined color
     */
    static const Color Cyan;

    /**
     * \brief White predefined color
     */
    static const Color White;

    /**
     * \brief DarkGray predefined color
     */
    static const Color DarkGray;

    /**
     * \brief DarkRed predefined color
     */
    static const Color DarkRed;

    /**
     * \brief DarkGreen predefined color
     */
    static const Color DarkGreen;

    /**
     * \brief DarkBlue predefined color
     */
    static const Color DarkBlue;

    /**
     * \brief DarkYellow predefined color
     */
    static const Color DarkYellow;

    /**
     * \brief DarkMagenta predefined color
     */
    static const Color DarkMagenta;

    /**
     * \brief DarkCyan predefined color
     */
    static const Color DarkCyan;

    /**
     * \brief Gray predefined color
     */
    static const Color Gray;

    /**
     * \brief Translates color component from [0, 255] to [0, 1000]
     * \return Red color component
     */
    uint16_t cursesRed() const;

    /**
     * \brief Translates color component from [0, 255] to [0, 1000]
     * \return Green color component
     */
    uint16_t cursesGreen() const;

    /**
     * \brief Translates color component from [0, 255] to [0, 1000]
     * \return Blue color component
     */
    uint16_t cursesBlue() const;

    /**
     * \brief Red component in color
     */
    uint8_t r;

    /**
     * \brief Green component in color
     */
    uint8_t g;

    /**
     * \brief Blue component in color
     */
    uint8_t b;
};
}