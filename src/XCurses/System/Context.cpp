#include <XCurses/System/Context.h>

#include <algorithm>
#include <stdexcept>

#include <PDCurses/curses.h>

#include <XCurses/System/Input.h>
#include <XCurses/Graphics/Widget.h>
#include <XCurses/System/TreeNode.h>
#include <XCurses/Graphics/Container.h>
#include <XCurses/System/ContextSystem.h>
#include <XCurses/Graphics/RootContainer.h>

namespace xcur {
Object::Ptr<Context> Context::create()
{
    auto context = std::shared_ptr<Context>(new Context());
    context->m_rootContainer->setContext(context);
    return context;
}

Context::Context() :
    m_rootContainer(RootContainer::create()),
    m_virtualScreen(VirtualScreen::create()),
    m_widgetTreeRoot(detail::TreeNode::create(m_rootContainer))
{
}

void Context::handleEvents() const
{
    Input::handleEvents(m_virtualScreen);
}

void Context::update(float dt)
{
    m_virtualScreen->update(dt);
    m_widgetTreeRoot->update(dt);
}

void Context::draw() const
{
    m_widgetTreeRoot->draw();
    m_virtualScreen->draw();
}

Status Context::add(Object::Ptr<Widget> widget)
{
    // If widget already exists
    if (has(widget)) {
        return Status::Err;
    }

    auto container = std::dynamic_pointer_cast<Container>(widget);
    // If widget is container
    if (container != nullptr) {
        return addContainerWidget(container);
    }
    else {
        return addSingleWidget(widget);
    }
}

Status Context::remove(Object::Ptr<Widget> widget)
{
    auto foundNode = m_widgetTreeRoot->findInSubtreeByWidget(widget);
    // If node not found
    if (foundNode == nullptr) {
        return Status::Err;
    }

    foundNode->getParent()->remove(widget);
    widget->setContext(nullptr);
    return Status::Ok;
}

void Context::addToVirtualScreen(Object::PtrConst<Widget> widget, const Char& ch, const Vector2i& position) const
{
    if (widget == nullptr) {
        throw std::runtime_error("Widget pointer is nullptr");
    }

    // If widget can't draw on the position
    if (!widget->isIntoVisibleArea(position)) {
        return;
    }

    Vector2i endPosition = position + widget->getPosition();
    auto parent = widget->getParent();
    // Pass through all parent widgets
    while (parent != nullptr) {
        endPosition += parent->getPosition();
        parent = parent->getParent();
    }
    m_virtualScreen->addChar(ch, endPosition);
}

void Context::addToVirtualScreen(Object::PtrConst<Widget> widget, const String& str, const Vector2i& position) const
{
    if (widget == nullptr) {
        throw std::runtime_error("Widget pointer is nullptr");
    }

    // If widget can't draw on the position
    if (!widget->isIntoVisibleArea(position)) {
        return;
    }

    Vector2i endPosition = position + widget->getPosition();
    auto parent = widget->getParent();
    // Pass through all parent widgets
    while (parent != nullptr) {
        endPosition += parent->getPosition();
        parent = parent->getParent();
    }
    m_virtualScreen->addString(str, endPosition);
}

Object::Ptr<Widget> Context::getActiveInputWidget() const
{
    return m_virtualScreen->getActiveInputWidget();
}

bool Context::isActiveInputWidget(Object::Ptr<Widget> inputWidget) const
{
    return m_virtualScreen->isActiveInputWidget(inputWidget);
}

bool Context::has(Object::Ptr<Widget> widget) const
{
    return m_widgetTreeRoot->has(widget);
}

void Context::widgetToFront(Object::Ptr<Widget> widget) const
{
    auto foundNode = m_widgetTreeRoot->findInSubtreeByWidget(widget);
    // if node found
    if (foundNode != nullptr) {
        foundNode->getParent()->widgetToFront(widget);
    }
}

void Context::setContextSystem(Object::Ptr<ContextSystem> contextSystem)
{
    m_contextSystem = contextSystem;
}

Object::Ptr<ContextSystem> Context::getContextSystem() const
{
    return m_contextSystem.lock();
}

Status Context::addContainerWidget(Object::Ptr<Container> container)
{
    Status addStatus = addSingleWidget(container);
    // If add container end with error
    if (addStatus == Status::Err) {
        return Status::Err;
    }
    for (auto childIt = container->begin(); childIt != container->end(); ++childIt) {
        add(*childIt);
    }
    return Status::Ok;
}

Status Context::addSingleWidget(Object::Ptr<Widget> widget)
{
    // If widget has parent
    if (widget->getParent() != nullptr) {
        auto parent = m_widgetTreeRoot->findInSubtreeByWidget(std::dynamic_pointer_cast<Widget>(widget->getParent()));
        // If parent is wrong
        if (parent == nullptr) {
            return Status::Err;
        }
        parent->add(widget);
    }
    else {
        m_widgetTreeRoot->add(widget);
        m_rootContainer->add(widget);
    }
    widget->setContext(shared_from_this());

    return Status::Ok;
}
}
