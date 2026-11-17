#include <iostream>
#include <string>
using namespace std;

// Singleton: only one AppSettings object can ever exist
class AppSettings {
    string theme; int fontSize;
    AppSettings() : theme("Light"), fontSize(12) {
        cout << "AppSettings instance created" << endl;
    }
public:
    AppSettings(const AppSettings&) = delete;
    AppSettings& operator=(const AppSettings&) = delete;
    static AppSettings& getInstance() {
        static AppSettings instance;     // created once, on first use
        return instance;
    }
    void setTheme(const string& t) { theme = t; }
    void setFontSize(int s) { fontSize = s; }
    void show() const { cout << "Theme: " << theme << ", Font size: " << fontSize << endl; }
};

int main() {
    cout << "Name: Puneet Kumar" << endl;
    AppSettings& s1 = AppSettings::getInstance();   // call 1
    s1.show();
    s1.setTheme("Dark");
    AppSettings& s2 = AppSettings::getInstance();   // call 2 - same object
    s2.setFontSize(16);
    s2.show();
    cout << "Same instance? " << (&s1 == &s2 ? "Yes" : "No") << endl;
    return 0;
}
