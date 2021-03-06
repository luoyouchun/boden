
#include <bdn/ui/Window.h>

#include <bdn/Application.h>
#include <bdn/debug.h>
#include <bdn/ui/UIApplicationController.h>

#include <sstream>

namespace bdn::ui
{
    namespace detail
    {
        VIEW_CORE_REGISTRY_IMPLEMENTATION(Window)
    }

    String Window::orientationToString(Window::Orientation orientation)
    {
        using namespace std::string_literals;
        std::stringstream str;
        if (orientation & Orientation::Portrait) {
            str << "Portrait"s;
        }
        if (orientation & Orientation::LandscapeLeft) {
            if (str.tellp() != 0) {
                str << " | ";
            }
            str << "LandscapeLeft"s;
        }
        if (orientation & Orientation::LandscapeRight) {
            if (str.tellp() != 0) {
                str << " | ";
            }
            str << "LandscapeRight"s;
        }
        if (orientation & Orientation::PortraitUpsideDown) {
            if (str.tellp() != 0) {
                str << " | ";
            }
            str << "PortraitUpsideDown"s;
        }
        return str.str();
    }

    Window::Window(std::shared_ptr<ViewCoreFactory> viewCoreFactory) : View(std::move(viewCoreFactory))
    {
        detail::VIEW_CORE_REGISTER(Window, View::viewCoreFactory());

        visible = false;
        allowedOrientations = Orientation::All;

        registerCoreCreatingProperties(this, &visible, &contentView, &geometry, &contentGeometry);
        contentView.onChange() += [=](auto &property) { _contentView.update(shared_from_this(), property.get()); };
    }

    std::list<std::shared_ptr<View>> Window::childViews()
    {
        assert(Application::isMainThread());
        if (contentView.get()) {
            return {contentView.get()};
        }
        return {};
    }

    void Window::removeAllChildViews() { contentView = nullptr; }

    void Window::childViewStolen(const std::shared_ptr<View> &childView)
    {
        assert(Application::isMainThread());

        if (childView == contentView.get()) {
            contentView = nullptr;
        }
    }

    void Window::bindViewCore()
    {
        View::bindViewCore();

        auto windowCore = View::core<Window::Core>();

        windowCore->contentView.bind(contentView);
        windowCore->title.bind(title);

        windowCore->allowedOrientations.bind(allowedOrientations); //, BindMode::unidirectional);
        windowCore->currentOrientation.bind(currentOrientation);   //, BindMode::unidirectional);
        windowCore->contentGeometry.bind(internalContentGeometry);
    }
}
