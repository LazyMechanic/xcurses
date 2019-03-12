#include <XCurses/Graphics/Container.h>

#include <algorithm>

#include <XCurses/Graphics/Context.h>

namespace xcur {
Object::Ptr<Container> Container::create()
{
	return std::shared_ptr<Container>(new Container());
}

void Container::update(float dt)
{
    /* full virtual func */
}

void Container::draw()
{
    /* full virtual func */
}

void Container::setPosition(const Vector2u& newPos)
{
	Widget::setPosition(newPos);
    for (auto& child : m_childWidgets) {
		child->setPosition(newPos);
    }
}

void Container::move(const Vector2u& deltaPos)
{
	setPosition(getPosition() + deltaPos);
}

Status Container::add(Object::Ptr<Widget> widget)
{
    // If widget has parent already
    if (widget->getParent() != nullptr) {
        return Status::Err;
    }

    widget->setParent(std::dynamic_pointer_cast<Container>(shared_from_this()));
    m_childWidgets.push_back(widget);

    // If container was added in context and has ptr to it
    if (getContext() != nullptr) {
        getContext()->add(widget);
    }

    return Status::Ok;
}

Status Container::remove(Object::Ptr<Widget> widget)
{
    auto widgetIt = find(widget);
    // If widget not found
    if (widgetIt == m_childWidgets.end()) {
        return Status::Err;
    }

    m_childWidgets.erase(widgetIt);

    // If container was added in context and has ptr to it
    if (getContext() != nullptr) {
        getContext()->remove(widget);
    }

    return Status::Ok;
}

bool Container::has(Object::Ptr<Widget> widget)
{
    return find(widget) != m_childWidgets.end();
}

void Container::widgetToFront(Object::Ptr<Widget> widget)
{
    auto foundWidget = find(widget);
    // If widget found
    if (foundWidget != end()) {
        m_childWidgets.splice(m_childWidgets.end(), m_childWidgets, foundWidget);
        if (getContext() != nullptr) {
            getContext()->widgetToFront(widget);
        }
    }
}

std::list<Object::Ptr<Widget>>::const_iterator Container::begin() const
{
    return m_childWidgets.begin();
}

std::list<Object::Ptr<Widget>>::const_iterator Container::end() const
{
    return m_childWidgets.end();
}

std::list<Object::Ptr<Widget>>::const_iterator Container::find(Object::Ptr<Widget> widget) const
{
    return std::find_if(
        m_childWidgets.begin(),
        m_childWidgets.end(),
        [&widget](const Object::Ptr<Widget>& checkWidget) {
        return widget == checkWidget;
    });
}
}
