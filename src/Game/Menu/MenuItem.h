#ifndef PA2_HEARTHSTONE_MENUITEM_H
#define PA2_HEARTHSTONE_MENUITEM_H

#include <vector>
#include <string>
#include <functional>

/**
 * Class that represents the menu item
 */
class MenuItem {
public:
    /** Constructor which has an optional parameter that is called whenever we select this item*/
    MenuItem(std::string value, std::vector<int> ref, std::string header = "", std::function<void(void)> const& func = [](void){}) : value(value),header(header), ref(ref), func(func) {};
    /** Constructor that takes reference to a function which handles text input */
    MenuItem(std::string value, std::string header, std::function<bool(std::string,std::string*)> strInputFunc) : value(value),header(header), strInputFunc(strInputFunc) {};


    std::string value;
    std::string header;
    std::vector<int> ref;
    const std::function<void(void)> func;
    const std::function<bool(std::string, std::string * out)> strInputFunc = nullptr;

};

#endif //PA2_HEARTHSTONE_MENUITEM_H